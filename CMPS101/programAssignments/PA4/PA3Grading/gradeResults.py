# Autograder for PA3

import sys
import random
import math
import pprint

pp = pprint.PrettyPrinter(indent=2)

POINTS_PER_INPUT = 6

def pointRounding(percent):
	# points = round(POINTS_PER_INPUT * percent)
	# if percent != 1 and points == POINTS_PER_INPUT:
	# 	points = POINTS_PER_INPUT-1
	# return points

	if percent == 1:
		return 6
	elif percent >50:
		return 5
	elif percent > 0:
		return 4
	else: 
		return 2

def buildGraphFromFile(inputFile):
	with open(inputFile, "r") as f:
		return buildGraph(f.readline())

def buildGraph(graphLine):
	try:
		graphLine = graphLine.split("\n")[0].split(", ")

		numVerts = int(graphLine[0])
		graph = {"size" : 0}

		for i in range(1, numVerts+1):
			graph[i] = set()
		
		for edge in graphLine[1:]:
			
			v = int(edge.split(" ")[0])
			u = int(edge.split(" ")[1])

			result = addEdge(v, u, graph)

			if result == -1:
				return {"error": "Graph contains a self loop", "order" : -100, "size":-100}

		graph["order"] = numVerts


		#dir
		#pp.pprint(graph)
		return graph
	except:
		return {"error": "Some element of the graph was poorly formed", "order" : -100, "size" : -100}

def addEdge(v, u, graph):
	v = int(v)
	u = int(u)

	if v == u:
		return -1

	if v in graph:
		if u in graph[v]:
			return 1
		else:
			graph[v].add(u)
	else:
		graph[v] = set([u])

	graph["size"] += 1
	return 0



def deleteEdge(v, u, graph):
	v = int(v)
	u = int(u)

	if v == u:
		return -1

	if v in graph:
		if u in graph[v]:
			graph[v].remove(u)
			graph["size"] -= 1

			return 0

	return 1

def answerGetSize(graph):
	return graph["size"]

def answerGetOrder(graph):
	return graph["order"]

def answerGetNeighborCount(graph, v):
	if v in graph:
		return len(graph[v])
	else:
		return 0

def getPrintedEdges(graph):
	edgeSet = []

	for v in range(1, graph["order"]+1):
		adj = list(graph[v])
		adj.sort()
		for u in adj:
			edgeSet.append("%s %s"%(v, u))

	return edgeSet

def distance(start, dest, graph):
	start = int(start)
	dest = int(dest)

	currentLevel = [start]
	nextLevel = []

	found = []

	level = 1
	while len(currentLevel) > 0:
		u = currentLevel.pop()

		for v in graph[u]:
			if v == dest:
				return level

			if v not in found:
				nextLevel.append(v)
				found.append(v)

		if len(nextLevel) > 0:
			level += 1
			currentLevel = nextLevel

	return -1

def isAcyclic(graph):
	marks = {}
	for u in range(1, graph["order"]+1):
		marks[u] = "UNDISCOVERED"

	stack = []
	for u in range(1, graph["order"]+1):
		if marks[u] == "UNDISCOVERED":
			stack = dfs(graph, marks, stack, u)
			if stack == "Cycle Found":
				return False

	return True

def topoSort(graph):
	marks = {}
	for u in range(1, graph["order"]+1):
		marks[u] = "UNDISCOVERED"

	stack = []
	for u in range(1, graph["order"]+1):
		if marks[u] == "UNDISCOVERED":
			stack = dfs(graph, marks, stack, u)
			if stack == "Cycle Found":
				return False

	return list(reversed(stack))

def dfs(graph, marks, stack, u):
	marks[u] = "INPROGRESS"

	for v in graph[u]:
		if marks[v] == "INPROGRESS":
			return "Cycle Found"
		if marks[v] == "UNDISCOVERED":
			result = dfs(graph, marks, stack, v)

			if result == "Cycle Found":
				return result

	marks[u] = "DONE"
	stack.append(str(u))
	return stack


def validGraph(graph):
	if "error" in graph:
		return False

	for v in graph:
		if v != "order" and v != "size":
			if not validVert(graph, v): 
				return False

	return True

def validVert(graph, vert):
	try:
		vert = int(vert)
		if vert >= 1 and vert <= graph["order"]:
			for u in graph[vert]:
				if u < 1 or u > graph["order"]:
					return False
		else:
			return False

		return True
	except:
		return False 

def compareGraphs(A, B):
	if answerGetOrder(A) != answerGetOrder(B):
		return False
	if answerGetSize(A) != answerGetSize(B):
		return False

	for vert in A:
		if validVert(A, vert):
			if vert not in B:
				return False
			if len(A[vert]) != len(B[vert]):
				return False

			for u in A[vert]:
				if u not in B[vert]:
					return False
	return True

def getMissingEdges(taGraph, studentGraph):
	studentEdges = [edge.replace(" ", "") for edge in getPrintedEdges(studentGraph)]


	missing = []
	for edge in getPrintedEdges(taGraph):
		if not (edge.replace(" ", "") in studentEdges):
			missing.append(edge)

	return missing

def validTopoSort(graph, tsort):
	processed = []
	tsort = tsort.strip().split(" ")
	if len(tsort) != graph["order"]:
		return False

	if len(tsort) != len(set(tsort)):
		return False

	for vert in tsort:
		try:
			for neighbor in graph[int(vert)]:
				if neighbor in processed:
					return False
			processed.append(vert)
		except:
			return False

	return True

def hasDuplicateEdges(line):
	edges = line.replace(", ", ",").replace(" ,", ",").split(",")
	return len(edges) != len(set(edges))

def getOperation(line):
	line = line.split(" ")
	return line[0], line[1:]

def answerOperations(inputFile, genAnswerKey):
	with open(inputFile, "r") as f:
		output = []
		line = f.readline()
		graph = buildGraph(line)

		if validGraph(graph):
			line = f.readline()
			while line:
				line = line.split("\n")[0]
				output.append(line)
				operation, operands = getOperation(line)

				if(operation == "GetSize"):
					if len(operands) == 0:
						output.append(answerGetSize(graph))
					else: 
						output.append("ERROR")

				elif operation == "GetOrder":
					if len(operands) == 0:
						output.append(answerGetOrder(graph))
					else:
						output.append("ERROR")

				elif operation == "GetOutDegree" :
					if len(operands) == 1 and validVert(graph, operands[0]):
						output.append(answerGetNeighborCount(graph, int(operands[0])))
					else:
						output.append("ERROR")

				elif operation == "PrintDigraph":
					if len(operands) == 0: 
						edgeSet = getPrintedEdges(graph)
						edgeSet = [str(graph["order"])] + edgeSet
						output.append(", ".join(edgeSet))
					else: 
						output.append("ERROR")

				elif operation == "AddEdge":

					if len(operands) == 2:
						if validVert(graph, operands[0]) and validVert(graph, operands[1]):
							result = addEdge(operands[0], operands[1], graph)

							output.append(result)
							# if result != -1:
							# 	output.append(result)
							# else:
							# 	output.append("ERROR")
						else:
							output.append("-1")
					else:
						output.append("ERROR")

				elif operation == "DeleteEdge":
					if len(operands) == 2:
						if validVert(graph, operands[0]) and validVert(graph, operands[1]):
							result = deleteEdge(operands[0], operands[1], graph)

							output.append(result)
							# if result != -1:
							# 	output.append(result)
							# else:
							# 	output.append("ERROR")
						else:
							output.append("-1")
					else:
						output.append("ERROR")

				elif operation == "Distance":
					if len(operands) == 2 and validVert(graph, operands[0]) and validVert(graph, operands[1]):
						dist = distance(operands[0], operands[1], graph)
						if dist >= 0: 
							output.append(dist)
						else:
							output.append("INF")
					else:
						output.append("ERROR")

				elif operation == "Acyclic":
					if len(operands) == 0:
						acyclic = isAcyclic(graph)
						if acyclic:
							output.append("YES")
						else:
							output.append("NO")
					else:
						output.append("ERROR")

				elif operation == "TopoSort":
					if len(operands) == 0:
						tSortedList = topoSort(graph)
						if tSortedList:
							if genAnswerKey:
								output.append(" ".join(tSortedList) )
							else:
								#add the state of the graph right now instead of the toposort:
								edgeSet = getPrintedEdges(graph)
								edgeSet = [str(graph["order"])] + edgeSet
								output.append(", ".join(edgeSet))
						else:
							output.append("IMPOSSIBLE")
					else:
						output.append("ERROR")

				else:
					output.append("ERROR")

				line = f.readline()
		else:
			output.append(line.split("\n")[0])
			output.append("ERROR")
	return output

def readAnswers(inputFile):
	#answer = []
	with open(inputFile, "r") as f:
		answer = [ line.replace("\n", "") for line in f.readlines()]

	return answer

def compareAnswerToExpected(taAnswer, studentAnswer):
	result = []

	if len(taAnswer) != len(studentAnswer):
		result.append(">>> STUDENT AND EXPECTED ANSWER ARE OF DIFFERENT LENGTHS, AUTOMATIC GRADING MAY FAIL!")
	
	pastCommand = ""
	for line in zip(taAnswer, studentAnswer):
		ta = line[0]
		student = line[1]

		# print("TA: %s"%ta)

		if(str(ta).replace(" ", "") == str(student).replace(" ", "")):
			result.append(student)
		elif pastCommand == "TopoSort":
			taGraph = buildGraph(ta)

			result.append(student)
			if not validTopoSort(taGraph, student):
				result.append(">>> TopoSort is not valid")

		elif pastCommand == "PrintDigraph":
			taGraph = buildGraph(ta)
			studentGraph = buildGraph(student)

			result.append(student)
			if "error" in studentGraph:
				result.append("\t>>> "+studentGraph["error"])

			else:
				if hasDuplicateEdges(student):
					result.append("\t>>> Output contains duplicate edges")

				# edgesWithVerticesOutOfOrder = checkEdgeVertexOrder(student)
				# numOutOrder = len(edgesWithVerticesOutOfOrder)
				# if numOutOrder > 0:
				# 	result.append("\t>>> %s edges have vertices listed in incorrect order: %s"%(numOutOrder, ", ".join(edgesWithVerticesOutOfOrder)))
				if not compareGraphs(taGraph, studentGraph):
					if taGraph["order"] != studentGraph["order"]:
						result.append("\t>>> Expected %s vertices, had %s"%(taGraph["order"], studentGraph["order"]))
					
					missing = getMissingEdges(taGraph, studentGraph)
					numMissing = len(missing)
					extra = getMissingEdges(studentGraph, taGraph)
					numExtra = len(extra)
					if missing != []:
						result.append("\t>>> Missing %s edges: %s"%(numMissing, ", ".join(missing)))
					if extra != []:
						result.append("\t>>> Contains %s extra edges: %s"%(numExtra, ", ".join(extra)))


		else:
			result.append("\t>>> Expected %s, had %s"%(ta, student))

		pastCommand = ta

	it = iter(taAnswer[len(studentAnswer):])
	for line in it:
		result.append(line)
		result.append("\t>>> Missing above line")
		try:
			result.append("\t>>> Expected: %s"%next(it))
		except:
			result.append("\t>>> Noneven number of lines!")

	for line in studentAnswer[len(taAnswer):]:
		result.append("\t>>> Found but not expecting: %s"%line)

	# result.append(" ")
	# result.append(">>> %s/%s: %s points"%(numRight, numQuestion, round((numRight/numQuestion)*4)))

	return result

def gradeResult(result):
	opperationBreakDown = {}
	operationsTypes = ["TopoSort", "GetSize", "GetOrder", "GetOutDegree", "Distance", 
					"AddEdge", "DeleteEdge", "PrintDigraph", "Acyclic", "NotAnOp", "MissingOrExtra"]

	total = 0
	wrong = 0

	for op in operationsTypes:
		opperationBreakDown[op]= {"num":0, "wrong":0}

	operationsTypes.append("NotAnOp")
	operationsTypes.append("ReallyIPromise")

	lastOp = ""
	opWrong = False

	for line in result:
		try:
			op = line.split(" ")[0]
			if op == "ReallyIPromise":
				op = "NotAnOp"
			if op in operationsTypes:
				lastOp = op
				opperationBreakDown[lastOp]["num"] += 1
				total += 1
				opWrong = False
			elif not opWrong and line.startswith("\t>>>"):
				opWrong = True
				opperationBreakDown[lastOp]["wrong"] += 1
				wrong += 1

			if line.startswith("\t>>> Found but not expecting") or line.startswith("\t>>> Missing above line"):
				opperationBreakDown["MissingOrExtra"]["wrong"] += 1
				wrong += 1
		except:
			wrong += 1


	result.append("---------------------------------------------------------------")
	result.append("Results:")

	if total == 0:
		if wrong == 0:
			correct = 1
			total = 1
		else:
			#result.append("0/1 = 0")
			correct = 0
			total = 1
	
	else:
		if opperationBreakDown["AddEdge"]["num"] > 100:
			total = 0
			wrong = 0
			for op in opperationBreakDown:
				if op != "AddEdge":
					total += opperationBreakDown[op]["num"]
					wrong += opperationBreakDown[op]["wrong"]
				else:
					total += round(opperationBreakDown[op]["num"]/50)
					wrong += round(opperationBreakDown[op]["wrong"]/50)

		correct = max(0, total - wrong)
	percent = correct/total
	points = pointRounding(percent)

		
	result.append("\t%s/%s = %s"%(correct, total, correct/total))
	result.append("\tPoints: %s"%points)

	return opperationBreakDown

def makeAnswerSheet(inputFile, outputfile):
	output = answerOperations(inputFile, True)
	with open(outputfile, "w") as f:
		for line in output:
			f.write("%s\n"%line)

if __name__ == "__main__":
	inputFile = sys.argv[1]	
	studentAnswerFile = sys.argv[2]	

	taAnswer = answerOperations(inputFile, False)
	studentAnswer = readAnswers(studentAnswerFile)

	# print("TA Answer:")
	# pp.pprint(taAnswer)
	# print("Student Answer:")
	# pp.pprint(studentAnswer)

	result = compareAnswerToExpected(taAnswer, studentAnswer)

	grade = gradeResult(result)

	#print("Comparison:")
	# pp.pprint(result)
	for line in result:
		print(line)

	#pp.pprint(grade)