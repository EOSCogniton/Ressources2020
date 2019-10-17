import scipy.io as sio
import json

def str2arr(name):
    """
    splits a test string name from nomenclature into an array of strings
    :param name: (str) test name
    :return: (arr of str) 11 size array with the parameters in the name string
    """
    name = name.split('_')
    name = [ #test
            name[0][0], #type
            name[0][1], #round
            #tire
            name[1][0], #brand
            name[1][1], #model
            #rim
            name[1][2:4], #diameter
            name[1][4], #width
            #physics
            *name[2:7]]
    return name

def value2glossary(params):
    """
    update global glossary with a new test
    :param params: (11-arr) parameter from test nomenclature
    :return: nothing, updates global glossary variable
    """
    global glossary

    if len(params)not in range(10,12):
        print("ERROR\t {}".format(len(params)))
        return False

    insertTest(params, glossary)


def insertTest(params,dico):
    """
    depth-insert array in graph levels
    use arrays for later json serialization
    :param params:
    :return: nothing
    """
    if len(params)==2:
        p, m = params
        try:
            if p in dico.keys():
               try:
                   if m not in dico[p]:
                       # add value only if not already there
                       dico[p].append(m)
               except AttributeError:
                   dico[p] = [m]
            else:
                dico[p] = [m]

        except AttributeError:
            # not a dictionary
           dico=dict()
           dico[p]= [m]
    else:
        p = params.pop(0)
        try:
            # add key on ly if it isn't already there
            if p not in dico.keys():
                dico[p] = dict()
        except AttributeError:
            #not a dictionary
           dico=dict()
           dico[p]= dict()

        insertTest(params, dico[p])


if __name__ == '__main__':
    fileNames = [
        *['R{}_Brake_Pacejka_89'.format(i) for i in range(5,9)],
        *['R{}_Corner_Pacejka_89'.format(i) for i in range(5, 9)]
    ]

    glossary = dict()

    for file in fileNames:
        testSet = sio.loadmat('dataFit/{}.mat'.format(file)).keys()
        for testName in testSet:
            if testName in ['__globals__', '__header__', '__version__']:
                continue
            testName = str2arr(testName)
            #print(testName)
            value2glossary(testName)

        with open('glossary/glossary.json','w') as f:
            json.dump(glossary, f)