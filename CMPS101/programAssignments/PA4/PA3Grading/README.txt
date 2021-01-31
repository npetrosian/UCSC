Set of files needed for grading PA3 (Programing Assignment 3) for CS101 Winter 2019.

Contents:
	- input
		A folder containing two subfolders, each holding the public and private inputs respectively.
		These files are used for grading.
	- gradeResults.py
		The python3 script used to generate scores for student output on specific inputs. 
		Usage: 
			python gradeResults.py <providedInputFile> <studentsGeneratedOutputFile>
		ex:
			python gradeResults.py input\public\input_a.txt studentOut.txt
	- answerKey
		A folder containing two subfolders, each holding sample answer keys for the public and private inputs. 
		This is not used in grading unless one needs to check a student's output by hand.