#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Fri Nov  1 14:46:26 2019 @author(s): MSO
affichage gantt LAS en partant du fichier csv 
"""


import xml.etree.ElementTree as ET
tree = ET.parse('ganttLAS_v03.xml')
root = tree.getroot()
tasks = root[51]
resources =root[52]
assignements = root[53]

taskEnd = len(tasks)
#%%


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


#%% task dictionary and latex

def section(title, note, level, priority):
    # strip the blank spaces and fix underscore
    title = clearTitle(title)
    note = clearNote(note)
    # priority level star symbol
    if priority > 500:
        title = "$\\bigstar$ " + title
    if level >=3:
        latex = "\t"*level+"\\paragraph{{{}}} {}".format(title, note)
    elif level==1:
        latex = "\\newpage \n \\section*{{{}}} \n \par {}".format(title, note)
    else:
        latex = "\t"*level+"\\"+"sub"*level+"section*{{{}}} \n \par {}".format(title, note)
    return latex


taskDict = dict()

with open("tasks.tex", "w") as f:
    for i in range(1,taskEnd):
        t = tasks[i]
        uid = t.find("UID").text
        name = t.find("Name").text
        note = t.find("Notes")
        # might be None
        note = "" if note is None else note.text
        outlv = int(t.find("OutlineLevel").text)
        priority = int(t.find("Priority").text)
        active = int(t.find("Active").text)
        # latex outline 
        print(section(name, note, outlv, priority), file=f)
        # task dictionary
        taskDict[uid] = {"name":name, 
                "outlv": outlv, 
                "priority": priority,
                "active": active,
                "note": note}


#%% resources dictionary
resourceDict = dict()

for r in resources:
    uid = r.find("UID").text
    name = r.find("Name").text
    #print(uid, name)
    resourceDict[uid] = {"name":name}

#%% dolist dictionary

dolistRes = dict()
dolistTask = dict()

for a in assignements:
    resUid = a.find("ResourceUID").text
    taskUid = a.find("TaskUID").text
    #print("resource:", resUid, "task:", taskUid)
    # dolist resources
    if resUid in dolistRes.keys():
        dolistRes[resUid].add(taskUid)
    else:
        dolistRes[resUid] = set([taskUid])
    # dolist tasks
    if taskUid in dolistTask.keys():
        dolistTask[taskUid].add(resUid)
    else:
        dolistTask[taskUid] = set([resUid])

#%% create dolist latex 

def person(name, note):
    text = "\n \n \\newpage \\section*{{{}}} \n \\par {}".format(name, note)
    return text


def task(name, note, priority, peopleList = []):
    if priority > 500:
        name = "$\\bigstar$ " + name
    if peopleList !=[] :
        # fromat list to str
        peopleList = ", ".join(peopleList)
        text = "\\paragraph{{{}}} (avec {}) {}".format(clearTitle(name), peopleList,  clearNote(note))
    else:
        text = "\\paragraph{{{}}} {}".format(clearTitle(name), clearNote(note))
    return text

with open("team.tex", "w") as f:
    for resId, resProp in resourceDict.items():
        name = resProp["name"]
        print(person(name,"personal notes"), file=f)
        for taskId in dolistRes[resId]:
            peopleList = list(resourceDict[pid]["name"] for pid in dolistTask[taskId])
            taskName = taskDict[taskId]["name"]
            taskNote =  taskDict[taskId]["note"]
            priority = taskDict[taskId]["priority"]
            # print only if priority is normal or higher
            if priority >= 500:
                if [name] == peopleList:
                    # task is not shared with others
                    print(task(taskName,taskNote, priority), file=f)
                elif name in peopleList:
                    # task is shared with others
                    # remove the current person
                    peopleList.remove(name)
                    print(task(taskName,taskNote,priority, peopleList), file=f)

