import json

with open('glossary/glossary.json') as f:
    glossary = json.load(f)


def searchUpLow(query):
    """
    search nearest fit available  by fixing up to pressure (6 params)
    :param query: (str arr) dimension <11 query parameters
    :return: (list) 2 test names fro upper and lower bound with respect to the query 
    """

    def recursiveSearch(query, dico, ans, upper=True):
        """
        recursively search in dico.keys() for the first greater value of the query array
        :param query: (str arr) array of query parameters (str)
        :param dico: glossary dictionary up to level
        :param ans: cumulated answer array of str
        :param upper: (Bool) whether to search for the upper or lower bound
        :return: recursively, the nearest bound per parameter
        """
        if len(query) > 1:
            q = int(query.pop(0))
            # covert keys to numbers
            keys = [int(k) for k in dico.keys()]
            # pick the first one
            key = keys[0]
            # search for the uppt or lower bound
            for k in keys:
                if upper:
                    key = k if k >= q else key
                else:
                    key = k if k <= q else key
            # key back to str
            key = str(key)
            # store the result
            ans.append(key)
            # iterate to the next parameter in the list
            recursiveSearch(query, dico[key], ans, upper)
        elif len(query) == 1:
            q = int(query.pop(0))
            keys = [int(k) for k in dico]
            key = keys[0]
            for k in keys:
                if upper:
                    key = k if k >= q else key
                else:
                    key = k if k <= q else key

            ans.append(str(key))
        else:
            return


    global glossary
    # stop to physical conditions to interpolate
    _ = glossary
    stop = 7 # to stop after pressure
    for i in range(stop):
        _ = _[query[i]]

    # upper bound
    up = query[:stop]
    recursiveSearch(query[stop:], _, up, True)
    # lower bound
    lo = query[:stop]
    recursiveSearch(query[stop:], _, lo, upper=False)

    return [arr2str(lo), arr2str(up)]


def searchCombi(query):
    """
    search all the available combination for a incomplete existing query
    use a set since the key order doesn't matter (afterall you need a mean)
    :param query: (list of str) query up to a fized parameter
    :return: (set) of str keys to get the fit coeffs
    """

    def recursiveSearch(dico, ans, root):
        """
        in-depth log of all dico combination keys stating with root
        :param dico:
        :param ans:
        :param root:
        :return:
        """
        ans.remove(root)
        if type(dico) == dict:
            for k in dico.keys():
                next = '_'.join([root, k])
                ans.add(next)
                recursiveSearch(dico[k], ans, next)
        else:
            for val in dico:
                next = '_'.join([root, val])
                ans.add(next)


    global glossary
    # query length determines the search depth
    _ = glossary
    for q in query:
        _ = _[q]
    # query root to ans
    root = arr2str(query)
    ans = set([root])
    recursiveSearch(_, ans, root)
    return ans


def searchNext(query):
    """
    search for the next parameter available values following the nomenclature
    :param query: (list) of string parameters
    :return: (list) str key values to complete the qgiven query
    """
    global glossary
    # query length to stop at the right glossary level
    _ = glossary
    for q in query:
        _ = _[q]
    return list(_.keys())


def arr2str(arr):
    """
    convert a str array of aswer to a str key to acces the fit coeffs
    :param arr: (str arr)
    :return: str nomenclature encoded
    """
    arr = [ #test
            "".join(arr[0:2]),
            #tire
            "".join(arr[2:6]),
            #physics
            *arr[6:]]

    return '_'.join(arr)


if __name__ == '__main__':
    
    loadGlossary('glossary/brake.json')

    query = [
        #test
        "B",  #type
        "8",  #round

        #tire
        "C",  #make
        "B",  #model
        "13", #rim diameter
        "7",  #rim width

        #physics
        "12f", #pressure
        "25",  #speed
#        "100", #load (FZ)

        #geometry
#        "0",  #camber
#        "0"  #toe
    ]

    # upper low test
    #ans = searchUpLow(query)
    #print("upper:{}\nquery:{}\nlower:{}".format(ans[1],arr2str(query),ans[0]))

    # Fz search test query
    #ans = searchCombi(query)
    #print(ans)

    # Next serch test
    ans =  searchNext(query)
    print(ans)