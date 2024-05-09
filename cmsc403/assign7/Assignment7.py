# Javeria Hanif
# Apr 13, 2024 
# CMSC 403 Spring 2024
# Assignment7.py is a python program that uses python package tkinter to display a 
# collection of rectangles on a canvas and uses rectpack library to ensure that 
# the rectangles exist on the given canvas space. 

# import statements 
import tkinter as tk
from rectpack import newPacker
import sys

# this class contains a constructor that stores height and width.  
# this class creates a canvas object with the given height and width using tkinter package 
class CustomCanvas: 
    def __init__(self, height: int, width: int): 
        # constructor creates a canvas object 
        self.canvas = tk.Canvas(height=height, width=width)
        # assigns height and width to instance variables 
        self.height = height
        self.width = width 

# this is a rectangle class that contains a constructor with height, width, and x, y coordinates 
class Rectangle: 
    # constructor initializes rectangle object with height, weight, x and y coordinates 
    def __init__(self, height: int, width: int, x: int = 0, y: int = 0):
        # assigns height, width, x, and y to instance variables
        self.height = height
        self.width = width 
        self.x = x
        self.y = y

        # function represents rectangle object as string 
        def __repr__(self):
            return f"Rectangle(width={self.width}, height={self.height}, x={self.x}, y={self.y})"

# function packs a list of rectangles within a given canvas size using rectpack  
# also returns a list of placed rectangles with updated x and y coordinates
def pack(allRect, canvasSize):
    # initializes new packer from rectpack library
    packer = newPacker()

    # iterates though the list of rectangles and adds rectangles to the packer
    for r in allRect: 
        # adds each rectangle's height and width to the packer
        packer.add_rect(r.height, r.width)

    # adds a bin with given canvas size to the packer
    # this is where rectangles are going to be packed within the given canvas size
    packer.add_bin(*canvasSize)

    # starts packing to fit rectangles within the canvas
    packer.pack()

    # gets the list of placed rectangles from the packer after packing
    packed_rects = packer.rect_list()
    rectangles = [] # empty list that stores the placed rectangles with the updated coordinates
    # iterates over each packed rectangle and gets the corresponding rectangle from the allRect list
    for rect in packed_rects:
        _, x, y, w, h, _ = rect # unpacks the coordinates and dimensions of the packed rectangle
        # appends a new rectangle object with the packed coordinates and dimensions to the list
        rectangles.append(Rectangle(h, w, x, y))

    # returns a list of rectangles with updated x and y coordinates
    return rectangles

# main function reads the filepath and processes a file containing canvas and rectangle dimensions 
def main():
    # gets the filepath as the second command line argument 
    filepath = sys.argv[1]

    # opens the file 
    with open(filepath, 'r') as file:
        lines = file.readlines() # reads the lines

    # first line in the file contains canvas's height and width separated by a comma
    canvas_dimensions = lines[0].strip().split(',')
    # parses canvas dimensions and coverts them to int type
    canvas_height = int(canvas_dimensions[0])
    canvas_width = int(canvas_dimensions[1])

    # creates a custom canvas object using the parsed canvas dimensions
    canvas = CustomCanvas(canvas_height, canvas_width)

    # rest of the lines represent the dimensions of each rectangle i.e. height and width
    # empty list that stores the rectangle objects 
    rectangles = []
    # iterates over the lines 
    for line in lines[1:]:
        rect_dimensions = line.strip().split(',') # rectangle dimensions separated by comma
        # parses each rectangle's dimensions and converts them into int type
        height = int(rect_dimensions[0])
        width = int(rect_dimensions[1])
        # appends new rectangle object to the list 
        rectangles.append(Rectangle(height, width))

    # initializes the window and gives it a title: Canvas
    window = tk.Tk()
    window.title = ("Canvas")
    
    # packs the canvas into window to display
    canvas.canvas.pack()

    # pack function is called to determine the placement of each rectangle within the canvas
    packed_rectangles = pack(rectangles, (canvas_height, canvas_width))

    # iterates through the list of packed rectangles and creates rectangles on the canvas at given locations 
    for rect in packed_rectangles:
        canvas.canvas.create_rectangle(rect.x, rect.y, rect.x+rect.width, rect.y+rect.height, border_color='black', fill_color='yellow')

    # starts the main event loop
    window.mainloop()

# checks if main function is running as a standalone or in a library
if __name__ == "__main__":
    main() # main function is called