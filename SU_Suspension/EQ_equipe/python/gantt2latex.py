#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Fri Nov  1 14:46:26 2019 @author(s): MSO
affichage gantt LAS en partant du fichier csv 
"""


import pandas as pd

filename = "Gantt LAS v1"
taskEnd= 100
ganttDf = pd.read_csv(filename+".csv", header=0, nrows=taskEnd)

def clearNote(text):
    text = str(text)
    return text if text!="nan" else ""

def clearTitle(text):
    text = text.replace("  ", "")
    return text


#%% create task latex

def section(title, note, level=0):
    # strip the blank spaces
    title = clearTitle(title)
    # underscore compliance
    title = title.replace("_", "\\textunderscore ")
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
people = set(ganttDf.values[:,5])

def person(name, note):
    text = "\\newpage \\section*{{{}}} \n \\par {}".format(name, note)
    return text


def task(name, note):
    text = "\\paragraph{{{}}} {}".format(clearTitle(name), clearNote(note))
    return text

with open("team.tex", "w") as f:
    for p in people:
        print(person(p,"personal notes"), file=f)
        for i in range(taskEnd):
            if p == ganttDf.values[i,5]:
                taskName = ganttDf.values[i,0]
                taskNote =  cleanNote(ganttDf.values[i,7])
                print(task(taskName,taskNote), file=f)
                




