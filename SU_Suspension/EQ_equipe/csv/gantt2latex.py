#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Fri Nov  1 14:46:26 2019 @author(s): MSO
affichage gantt LAS en partant du fichier csv 
"""


import pandas as pd

filename = "ganttLAS_v02"
taskEnd= 125
ganttDf = pd.read_csv(filename+".csv", header=0, nrows=taskEnd)

def clearNote(text):
    text = str(text)
    #fix underscore for latex
    text = text.replace("_", "\\_")
    return text if text!="nan" else ""

def clearTitle(text):
    # strip indentation spaces
    text = text.replace("  ", "")
    #fix underscore for latex
    text = text.replace("_", "\\_")
    return text


#%% create task latex

def section(title, note, level=0):
    # strip the blank spaces and fix underscore
    title = clearTitle(title)
    if level >=2:
        latex = "\t"*level+"\\paragraph{{{}}} {}".format(title, note)
    elif level==0:
        latex = "\\newpage \n \\section*{{{}}} \n \par {}".format(title, note)
    else:
        latex = "\t"*level+"\\"+"sub"*level+"section*{{{}}} \n \par {}".format(title, note)
    return latex


with open("tasks.tex", "w") as f:
    for i in range(taskEnd):
        name = ganttDf.values[i,0]
        note = clearNote(ganttDf.values[i,7])
        if name[0:4]==' '*4 :
            print(section(name, note, 2), file=f)
        elif name[0:2]==' '*2 :
            print(section(name, note, 1), file=f)
        else :
            print(section(name, note), file=f)
        

#%% create ressources latex 
people = set()
for p in ganttDf.values[:,5]:
    p = str(p) # for floar nan
    [people.add(x) for x in p.split(";")]

people.discard("nan")

def person(name, note):
    text = "\\newpage \\section*{{{}}} \n \\par {}".format(name, note)
    return text


def task(name, note, peopleList = []):
    if peopleList !=[] :
        # fromat list to str
        peopleList = ", ".join(peopleList)
        text = "\\paragraph{{{}}} (avec {}) {}".format(clearTitle(name), peopleList,  clearNote(note))
    else:
        text = "\\paragraph{{{}}} {}".format(clearTitle(name), clearNote(note))
    return text

with open("team.tex", "w") as f:
    for p in people:
        print(person(p,"personal notes"), file=f)
        for i in range(taskEnd):
            peopleList = ganttDf.values[i,5]
            taskName = ganttDf.values[i,0]
            taskNote =  clearNote(ganttDf.values[i,7])
            if p == peopleList:
                # task is not shared with others
                print(task(taskName,taskNote), file=f)
            elif p in str(peopleList).split(";"):
                # task is shared with others
                peopleList = str(peopleList).split(";")
                # remove the current person
                peopleList.remove(p)
                print(task(taskName,taskNote,peopleList) , file=f)

