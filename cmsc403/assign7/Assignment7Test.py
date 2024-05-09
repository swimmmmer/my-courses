import traceback
import sys
import functools
import time
from shapely.geometry import Polygon 
from shapely.geometry import box
from multiprocessing import Process


sucessfulImport = False

#Test importing the assignment as a package
print("\nImport Tests\n")
try:
	from Assignment7 import Rectangle
	from Assignment7 import pack
	sucessfulImport = True
	print("PASS: Rectangle & pack imported without error\n")
except Exception as e:
	print("FAIL: When trying to import Rectangle & pack got the following error: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")

if sucessfulImport == False:
	quit()


def createFourArgsRectangle():
	try:
		rect = Rectangle(10,20,1,2)
		print("PASS: Creating Rectangle with 4 args" + "\n")
	except Exception as e:
		print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), got an exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")

def testRectProperties():
	try:
		rect = Rectangle(10,20,1,2)
		height = rect.height
		width = rect.width
		x = rect.x
		y = rect.y

		if height != 10:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), we expected height to be 10 but was: " + str(height) + "\n")
			return
		if width != 20:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), we expected width to be 20 but was: " + str(width) + "\n")
			return
		if x != 1:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), we expected x to be 1 but was: " + str(x) + "\n")
			return
		if y != 2:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), we expected y to be 2 but was: " + str(y) + "\n")
			return

		print("PASS: Testing instantiated Rectangle properties" + "\n")
	except Exception as e:
		print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20,1,2), got an exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")

def createTwoArgsRectangle():
	try:
		rect = Rectangle(10,20)

		x = rect.x 
		y = rect.y

		if x != 0:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20), we expected x to be 0 but was: " + str(x) + "\n")
			return
		if y != 0:
			print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20), we expected y to be 0 but was: " + str(y) + "\n")
			return

		print("PASS: Creating Rectangle with 2 args" + "\n")
	except Exception as e:
		print("FAIL: When creating a Rectangle with the following constructor: Rectangle(10,20), got an exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")


def rectEquality(rect1, rect2):
	isEqual = True
	if rect1.height != rect2.height or rect1.width != rect2.width:
		isEqual = False
	return isEqual

def getRectList(aList):
	if aList == "25":
		return [Rectangle(75,75),Rectangle(25,25),Rectangle(50,50),Rectangle(100,100),Rectangle(61,61)]
	elif aList == "50":
		return [Rectangle(75,75), Rectangle(25,25), Rectangle(50,50), Rectangle(100,100), Rectangle(61,61), Rectangle(75,75), Rectangle(25,25), Rectangle(50,50), Rectangle(100,100), Rectangle(61,61)]
	elif aList == "75":
		return [Rectangle(75,75),Rectangle(25,25),Rectangle(50,50),Rectangle(100,100),Rectangle(61,61),Rectangle(75,75),Rectangle(25,25),Rectangle(50,50),Rectangle(100,100),Rectangle(61,61),Rectangle(45,125),Rectangle(25,25),Rectangle(125,20),Rectangle(50,200),Rectangle(61,61)]
	elif aList == "95":
		return [Rectangle(75,75),Rectangle(25,25),Rectangle(50,50),Rectangle(100,100),Rectangle(61,61),Rectangle(45,125),Rectangle(25,25),Rectangle(125,20),Rectangle(50,200),Rectangle(61,61),Rectangle(45,125),Rectangle(25,25),Rectangle(125,20),Rectangle(50,200),Rectangle(61,61),Rectangle(50,50),Rectangle(50,50),Rectangle(50,50),Rectangle(50,50),Rectangle(50,50),Rectangle(25,25),Rectangle(25,25),Rectangle(25,25),Rectangle(25,25)]
	else:
		return [] 

def rectInBounds(aRect, aCanvas):
	inBounds = True
	cHeight = aCanvas[0]
	cWidth = aCanvas[1]

	#Origin Point (Top Left) 
	if aRect.x < 0 or aRect.x > cWidth or aRect.y < 0 or aRect.y > cHeight:
		inBounds = False
	#Bottom Left
	elif aRect.x < 0 or aRect.x > cWidth or (aRect.y + aRect.height) < 0 or (aRect.y + aRect.height) > cHeight:
		inBounds = False
	#Top Right 
	elif (aRect.x + aRect.width) < 0 or (aRect.x + aRect.width) > cWidth or aRect.y < 0 or aRect.y > cHeight:
		inBounds = False
	#Bottom Right 
	elif (aRect.x + aRect.width) < 0 or (aRect.x + aRect.width) > cWidth or (aRect.y + aRect.height) < 0 or (aRect.y + aRect.height) > cHeight:
		inBounds = False

	return inBounds

def rectsToPolygons(allRects):
	polygons = []
	for r in allRects:
		polygons.append(box(r.x,r.y,(r.x+r.width),(r.y+r.height) ))
	return polygons

def validReturn():
	outputList = None
	try:
		#Create List of Rectangles 
		inputList = [Rectangle(20,20)] * 4
		#Create Tuple Canvas Size 
		canvasSize = (200,200)
		outputList = pack(inputList,canvasSize)
	except Exception as e:
		print("FAIL: When calling pack with valid arguments got an exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")
		return

	try:
		if isinstance(outputList,list):
			if len(outputList) == 4:
				if functools.reduce(lambda a,b : a==b,[isinstance(rect,Rectangle) for rect in outputList]): 
					for i,rect in enumerate(outputList):
						if rectEquality(rect, Rectangle(20,20)) == False:
							print("FAIL: Returned Rectangle was not logically equlivant to given rectangle at index " + str(i) + "\n")
							return
				else:
					print("FAIL: The returned list was not exclusively Rectangle objects" + "\n")
					return
			else:
				print("FAIL: The list returned by pack did not have the correct number of elements" + "\n")
				return
		else:
			print("FAIL: Pack did not reutrn a list" + "\n")
			return
	
		print("PASS: Return value of pack function is in the correct format" + "\n")

	except Exception as e: 
		print("FAIL: When testing the output of Pack, got an exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")

def testFill(aFill):
	#Call pack without exceptions 
	try:
		outputList = pack(getRectList(aFill),(300,300))
	except Exception as e:
		print("FAIL: Calling pack given the " + aFill + "% fill, we got the following exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")
		return
	try:
		#Test for correct number of rects returned
		if len(outputList) != len(getRectList(aFill)):
			print("FAIL: Calling pack given the " + aFill + "% fill, we got " + str(len(outputList)) + " Rectangles but expected " + str(len(getRectList(aFill))) + "\n")
			return

		#Test for staying in bounds 
		for i,rect in enumerate(outputList):
			#print("\tx1,y1: ("+str(rect.x) +","+ str(rect.y) +") x2,y2: ("+ str(rect.width + rect.x)  +","+  str(rect.height + rect.y) + ")")
			if not rectInBounds(rect,(300,300)):
				print("FAIL: Rectangle at index " + str(i) + " is partly off the canvas\n")
				return
		#Test for collisions 
		outputList = rectsToPolygons(outputList)
		for rect1 in outputList:
			for rect2 in outputList:
				if rect1.bounds != rect2.bounds:
					if rect1.within(rect2):
						print("FAIL: Rectangle with bounds " + str(rect1.bounds) + " intersects with rectangle " + str(rect2.bounds) + "\n")
						return

		print("PASS: " + aFill + "% fill packed correctly\n")

	except Exception as e:
		print("FAIL: While validating the output of pack, got the following exception: " + "\n\n".join(traceback.TracebackException.from_exception(e).format()) + "\n")

def test25():
	testFill("25")

def test50():
	testFill("50")

def test75():
	testFill("75")

def test95():
	testFill("95")


if __name__ == '__main__':  

	#Rectangle Tests 
	print("\nRectangle Tests\n")
	#Create Rectangle with four args 
	createFourArgsRectangle()
	#Get and Set all four properties 
	testRectProperties()
	#Create Rectangle with 2 args to test for default params 
	createTwoArgsRectangle()

	#Pack Tests 
	print("\nPack Tests\n")
	#Pack returns a list of rectangles 
	p1 = Process(target=validReturn, name='validReturn')
	p1.start();p1.join(timeout=3);p1.terminate()
	if p1.exitcode is None:
		print("FAIL: pack function timed out after 3 seconds\n")
	#Test 25% Fill 
	p1 = Process(target=test25, name='Process_test25')
	p1.start();p1.join(timeout=3);p1.terminate()
	if p1.exitcode is None:
		print("FAIL: pack function timed out after 3 seconds\n")
	#Test 50% Fill 
	p1 = Process(target=test50, name='Process_test50')
	p1.start();p1.join(timeout=3);p1.terminate()
	if p1.exitcode is None:
		print("FAIL: pack function timed out after 3 seconds\n")
	#Test 75% Fill
	p1 = Process(target=test75, name='Process_test75')
	p1.start();p1.join(timeout=10);p1.terminate()
	if p1.exitcode is None:
		print("FAIL: pack function timed out after 10 seconds\n")
	#Test 95% Fill 
	p1 = Process(target=test95, name='Process_test95')
	p1.start();p1.join(timeout=15);p1.terminate()
	if p1.exitcode is None:
		print("FAIL: pack function timed out after 15 seconds\n")

