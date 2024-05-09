



import csv
import folium


# Create an empty list to store the data from the CSV file
data = []
parts = []
richmond_map1 = folium.Map(location=[37.5407, -77.4360], zoom_start=12)

# Open and read the CSV file
with open("REI Mapping Data - Sheet1.csv", mode='r') as file:
   csvFile = csv.reader(file)
   for row in csvFile:
        data.append(row)

#iframe = folium.IFrame(html,width=100,height=100)

#popup = folium.Popup(iframe,max_width=100,height=100)

# Now, you can work with the data
for x in range(3):
 myS = str(data[x])
 parts = myS.split(',')

 num1 = str(parts[1])
 num2 = str(parts[2])


 num1 = num1.replace("'"," ")
 num2 = num2.replace("'"," ").replace("]"," ")

 numa = float(num1)
 nump = float(num2)
 
 # url = "https://lh3.googleusercontent.com/p/AF1QipPXW-4IyUXeH-_EtaE-JxOxMYizGlaVntZEMnQy=s1360-w1360-h1020"
 # width = "200" 
 # height = "300"

 html = "<h3>" + parts[0] + "</h3>" + "<p>" + parts[3] + "</p>" + "<p>" + parts[4] + "</p>" + '<img src="' + parts[5] + '" width="200" height="300">' 
 #html = "<h3>" + parts[0] + "</h3>" + "<p>" + parts[3] + "</p>" + '<img src="/images/biotech.jpg" style="width:500px">'

# html = "<h3>" + parts[0] + "</h3>" + "<p>" + parts[3] + "</p>" + '<img src="' + parts[4] + '" width="500" height="600">'
# html = f"<h3>{name}</h3><p>{hours}</p><img src='{image_url}' width='500' height='600'>"




 folium.Marker(location=[numa, nump], popup=html).add_to(richmond_map1)
 richmond_map1.save("richmond_map3213123.html")





