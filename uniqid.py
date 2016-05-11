import time, math, random
 
# port of uniqmodule.c to pure python by Derwentx, 
# inspired by http://gurukhalsa.me/2011/uniqid-in-python/

def uniqid(prefix='', more_entropy=False):
    m = time.time()
    sec = math.floor(m)
    usec = math.floor(1000000 * (m - sec))
    if more_entropy:
        lcg = random.random()
        uniqid = "%08x%05x%.8F" % (sec, usec, lcg*10)
    else:
        uniqid = '%8x%05x' %(sec, usec)

    uniqid = prefix + uniqid
    return uniqid