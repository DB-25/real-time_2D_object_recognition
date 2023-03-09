Name: Bennett Brain
Group Member: Dhruv Kamalesh Kumar

Part 9 video link: https://drive.google.com/file/d/1fyJXKAPOUb0AAJ4a4BAsvOk1OB2K-uhr/view?usp=sharing

OS: Windows 10 (Bennett), MAC (Dhruv)

File explanation:

VidDisplay.cpp is the controller, and calls the individual tasks as needed.
Task#.cpp is the functions needed for each of the tasks.  We wrote tasks 1-2 from scratch and used OpenCV functions for tasks 3-4.  Additional code relevant to each task can be found in VidDisplay.cpp
For example, the grassfire transform and growing/shrinking from that are both in task2.cpp, but the amount of calls and alternating between 4c and 8c are in VidDisplay.cpp

data.csv is our database
confusion_matrix.xls is our confusion matrix
project_report3.pdf is our project report


For running executables: Need databse file data.csv in folder with executables.  Keypresses:

"1" thresholds the video

"2" thresholds and then does morphological clean-up

"3" generates a region ID map, and colors in the 3 largest regions red, green, and blue, then the rest as shades of grey (after thresholding and cleanup)

"4" selects the largest central region (after thresholding and clean-up), generates the 7 HuMoments of the region, and displays just the selected region with its bounding box in frame

"5" asks for a label for the image, and prints the HuMoments from part 4 into a new line in the data.csv file.

"6" uses simple scaled-euclidian distance to find the closest match from the database to whatever is currently in frame

"7" uses knn-matching to find the closest match from the database to whatever is currently in frame

Part 8 was just manually entering data into the confusion matrix

Part 9 was a video uploaded to the link at the top of this readme


Extensions:

-Unknown Classification:  Put a distinctly-shaped object not in the database (i.e. pair of scissors) in frame, and hit "6" or "7".  It should show "UNKNOWN" on the screen

-Extra objects: we included 15 objects in our database instead of 10

Time Travel days: None