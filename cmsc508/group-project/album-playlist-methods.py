# Album methods:

@app.route('/albums', methods=['GET'])
def get_albums():
    # get parameters 
    id_regex = request.args.get('id')
    name_regex = request.args.get('name')
    record_label_regex = request.args.get('record_label')
    genre_regex = request.args.get('genre')
    release_date_regex = request.args.get('release_date')
    classification_regex = request.args.get('classification')
    duration_regex = request.args.get('duration')
    artist_id_regex = request.args.get('artist_id')

    # build the query 
    query = text("SELECT album.ID, album.name, album.record_label, album.genre, album.release_date, album.classification, TIME_FORMAT(album.duration, '%H:%i') AS duration, album.artist_ID, artist.name AS artist_name FROM album JOIN artist ON album.artist_ID = artist.ID WHERE"
                "(album.ID REGEXP :id_regex OR :id_regex IS NULL) AND"
                "(album.name REGEXP :name_regex OR :name_regex IS NULL) AND"
                "(album.record_label REGEXP :record_label_regex OR :record_label_regex IS NULL) AND"
                "(album.genre REGEXP :genre_regex OR :genre_regex IS NULL) AND"
                "(album.release_date REGEXP :release_date_regex OR :release_date_regex IS NULL) AND"
                "(album.classification REGEXP :classification_regex OR :classification_regex IS NULL) AND"
                "(album.duration REGEXP :duration_regex OR :duration_regex IS NULL) AND"
                "(album.artist_ID REGEXP :artist_id_regex OR :artist_id_regex IS NULL);")

    # execute the query 
    result = testExecution(db.session.execute(query, {
        'id_regex': id_regex,
        'name_regex': name_regex,
        'record_label_regex': record_label_regex,
        'genre_regex': genre_regex,
        'release_date_regex': release_date_regex,
        'classification_regex': classification_regex,
        'duration_regex': duration_regex,
        'artist_id_regex': artist_id_regex,
    }))

    # get result
    albums_list = [{
        'ID': album['ID'],
        'name': album['name'],
        'record_label': album['record_label'],
        'genre': album['genre'],
        'release_date': album['release_date'],
        'classification': album['classification'],
        'duration': album['duration'],
        'artist_ID': album['artist_ID'],
        'artist_name': album['artist_name']
    } for album in result]

    if albums_list:
        return jsonify(albums_list)
    return jsonify(message='No albums match the criteria.'), 404


@app.route('/albums/<int:album_id>', methods=['GET'])
def get_album_by_id(album_id):
    query = text("SELECT ID, name, record_label, genre, release_date, classification, TIME_FORMAT(duration, '%H:%i') AS duration, artist_ID FROM album WHERE ID = :album_id;")
    album_list = testExecution(db.session.execute(query, {'album_id': album_id}))

    if album_list:
        return jsonify(albums=album_list)
    return jsonify(message='Album not found.'), 404


@app.route('/albums/artist/<int:artist_id>', methods=['GET'])
def get_albums_by_artist_id(artist_id):
    query = text("SELECT ID, name, record_label, genre, release_date, classification, TIME_FORMAT(duration, '%H:%i') AS duration, artist_ID FROM album WHERE artist_ID = artist_id;")
    album_list = testExecution(db.session.execute(query, {'artist_id': artist_id}))

    if album_list:
        return jsonify(albums=album_list)
    return jsonify(message='No albums found for the artist ID.'), 404

@app.route('/add_album', methods=['POST'])
def add_album():
    # request JSON
    data = request.json
    name = data.get('name')
    record_label = data.get('record_label')
    genre = data.get('genre', None)
    release_date = data.get('release_date', datetime.now().strftime('%Y-%m-%d'))
    classification = data.get('classification')
    duration = data.get('duration')
    artist_ID = data.get('artist_ID')

    if not name or not record_label or not classification or not duration or not artist_ID:
        return jsonify({'error': 'Missing required fields for adding an album (name, record_label, classification, duration, artist_ID)'}), 400

    # build query
    query = text("INSERT INTO album (name, record_label, genre, release_date, classification, duration, artist_ID) VALUES (:name, :record_label, :genre, :release_date, :classification, :duration, :artist_ID);")
    
    # execute the query to insert a new album
    db.session.execute(query, {'name': name, 'record_label': record_label, 'genre': genre, 'release_date': release_date, 'classification': classification, 'duration': duration, 'artist_ID': artist_ID})
    db.session.commit()

    # get new album
    query_get = text("SELECT ID, name, record_label, genre, release_date, classification, TIME_FORMAT(duration, '%H:%i') AS duration, artist_ID FROM album WHERE name = :name;")
    album_list = testExecution(db.session.execute(query_get, {'name': name}))

    return jsonify({'message': 'Album added successfully', 'album': album_list[0]}), 201

@app.route('/update_album/<int:album_id>', methods=['PUT'])
def update_album(album_id):
    # request JSON
    data = request.json
    name = data.get('name')
    record_label = data.get('record_label')
    genre = data.get('genre')
    release_date = data.get('release_date')
    classification = data.get('classification')
    duration = data.get('duration')
    artist_ID = data.get('artist_ID')

    if not name or not record_label or not classification or not duration or not artist_ID:
        return jsonify({'error': 'Missing required fields for updating an album (name, record_label, classification, duration, artist_ID)'}), 400

    query = text("UPDATE album SET name = :name, record_label = :record_label, genre = :genre, release_date = :release_date, classification = :classification, duration = :duration, artist_ID = :artist_ID WHERE ID = :album_id;")
    db.session.execute(query, {'name': name, 'record_label': record_label, 'genre': genre, 'release_date': release_date, 'classification': classification, 'duration': duration, 'artist_ID': artist_ID, 'album_id': album_id})
    db.session.commit()

    logging.info('Executing update_album method...')
    logging.debug(f'Input data: {data}')

    query_get = text("SELECT ID, name, record_label, genre, release_date, classification, TIME_FORMAT(duration, '%H:%i') AS duration, artist_ID FROM album WHERE ID = :album_id;")
    album_list = testExecution(db.session.execute(query_get, {'album_id': album_id}))

    return jsonify({'message': 'Album updated successfully', 'album': album_list[0]}), 200

@app.route('/albums/<int:album_id>', methods=['DELETE'])
def delete_album(album_id):
    # set "database_album" to the album with given ID
    database_album = db.session.execute(text("SELECT * FROM album WHERE ID = :album_id"), {"album_id": album_id}).fetchone()

    # if database_album exists with given ID
    if database_album:
        # Delete the album
        db.session.execute(text("DELETE FROM album WHERE ID = :album_id"), {"album_id": album_id})
        db.session.commit()

        return jsonify({'message': 'The album is deleted successfully'})

    else:
        return jsonify({'message': 'album not found'})
    
# Playlist methods:

@app.route('/playlists', methods=['GET'])
def get_playlists():
    # get parameters 
    id_regex = request.args.get('id')
    name_regex = request.args.get('name')
    description_regex = request.args.get('description')
    duration_regex = request.args.get('duration')
    #user_regex = request.args.get('user')
    user_id_regex = request.args.get('user_id')

    # build the query 
    query = text("SELECT playlist.ID, playlist.name, playlist.description, TIME_FORMAT(playlist.duration, '%H:%i') AS duration, playlist.user_ID, user.user_name AS user_name FROM playlist JOIN user ON playlist.user_ID = user.ID WHERE"
                "(playlist.ID REGEXP :id_regex OR :id_regex IS NULL) AND"
                "(playlist.name REGEXP :name_regex OR :name_regex IS NULL) AND"
                "(playlist.description REGEXP :description_regex OR :description_regex IS NULL) AND"
                "(playlist.duration REGEXP :duration_regex OR :duration_regex IS NULL) AND"
                #"(user.user_name REGEXP :user_regex OR user_regex IS NULL) AND" 
                "(user.ID REGEXP :user_id_regex OR :user_id_regex IS NULL);")
    # execute the query 
    result =  testExecution(db.session.execute(query, {'id_regex': id_regex, 'name_regex': name_regex, 'description_regex': description_regex, 'duration_regex': duration_regex, 'user_id_regex': user_id_regex}))


    # get result
    #playlists_list = [{'ID': playlist.ID, 'name': playlist.name, 'description': playlist.description, 'duration': playlist.duration, 'user_ID': playlist.user_ID, 'Username': playlist.user_name} for playlist in result]
    playlists_list = [{'ID': playlist['ID'], 'name': playlist['name'], 'description': playlist['description'], 'duration': playlist['duration'], 'user_ID': playlist['user_ID'], 'Username': playlist['user_name']} for playlist in result]

    if playlists_list:
        return jsonify(playlists_list)
    return jsonify(message='No playlists match the criteria.'), 404

@app.route('/playlists/<int:playlist_id>', methods=['GET'])
def get_playlist_by_id(playlist_id):
    query = text("SELECT ID, name, description, TIME_FORMAT(duration, '%H:%i') AS duration, user_ID FROM playlist WHERE id = :playlist_id;")
    playlist_list = testExecution(db.session.execute(query, {'playlist_id': playlist_id}))
    if playlist_list:
        return jsonify(playlists=playlist_list)
    return jsonify(message='Playlist not found.'), 404

@app.route('/playlists/user/<int:user_id>', methods=['GET'])
def get_playlists_by_user_id(user_id):
    query = text("SELECT ID, name, description, TIME_FORMAT(duration, '%H:%i') AS duration, user_ID FROM playlist WHERE user_ID = :user_id;")
    playlist_list = testExecution(db.session.execute(query, {'user_id': user_id}))
    if playlist_list:
        return jsonify(playlists=playlist_list)
    return jsonify(message='No playlists found for the user ID.'), 404

@app.route('/add_playlist', methods=['POST'])
def add_playlist():
    # request JSON
    data = request.json
    name = data.get('name')
    description = data.get('description', None)
    duration = data.get('duration')
    user_ID = data.get('user_ID')

    if not name or not duration or not user_ID:
        return jsonify({'error': 'Missing required fields for adding a playlist (name, duration, user_ID)'}), 400

    # build query
    query = text("INSERT INTO playlist (name, description, duration, user_ID) VALUES (:name, :description, :duration, :user_ID);")
    # execute the query to insert a new playlist
    db.session.execute(query, {'name': name, 'description': description, 'duration': duration, 'user_ID': user_ID})
    db.session.commit()

    # get new playlist 
    query_get = text("SELECT ID, name, description, TIME_FORMAT(duration, '%H:%i') AS duration, user_ID FROM playlist WHERE name = :name;")
    playlist_list = testExecution(db.session.execute(query_get, {'name': name}))

    return jsonify({'message': 'Playlist added successfully', 'playlist': playlist_list[0]}), 201

@app.route('/update_playlist/<int:playlist_id>', methods=['PUT'])
def update_playlist(playlist_id):
    # request JSON
    data = request.json
    name = data.get('name')
    description = data.get('description', None)
    duration = data.get('duration')
    user_ID = data.get('user_ID')

    if not name or not duration or not user_ID:
        return jsonify({'error': 'Missing required fields for updating a playlist (name, duration, user_ID)'}), 400

    query = text("UPDATE playlist SET name = :name, description = :description, duration = :duration, user_ID = :user_ID WHERE ID = :playlist_id;")
    db.session.execute(query, {'name': name, 'description': description, 'duration': duration, 'user_ID': user_ID, 'playlist_id': playlist_id})
    db.session.commit()

    logging.info('Executing update_playlist method...')
    logging.debug(f'Input data: {data}')

    query_get = text("SELECT ID, name, description, TIME_FORMAT(duration, '%H:%i') AS duration, user_ID FROM playlist WHERE ID = :playlist_id;")
    playlist_list = testExecution(db.session.execute(query_get, {'playlist_id': playlist_id}))

    return jsonify({'message': 'Playlist updated successfully', 'playlist': playlist_list[0]}), 200


@app.route('/playlists/<int:playlist_id>', methods=['DELETE'])
def delete_playlist(playlist_id):
    # set "database_playlist" to the playlist with given ID
    database_playlist = db.session.execute(text("SELECT * FROM playlist WHERE ID = :playlist_id"), {"playlist_id": playlist_id}).fetchone()

    # if database_playlist exists with given ID
    if database_playlist:
        # Delete the playlist
        db.session.execute(text("DELETE FROM playlist WHERE ID = :playlist_id"), {"playlist_id": playlist_id})
        db.session.commit()

        return jsonify({'message': 'The playlist is deleted successfully'})


    else:
        return jsonify({'message': 'Playlist not found'})
    