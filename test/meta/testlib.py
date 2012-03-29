
def sz(v):
    return '"'+str(v).replace('"', '\\"')+'"'

def x(a):
    return [ { "val" : v } if type(v) is not list
                         else { "val" : v[0], "exp": { "v":v[1] }} for v in a ]

def xs(a):
     return [ { "val" : sz(v) } if type(v) is not list
                              else { "val" : sz(v[0]), "exp": { "v":sz(v[1])} } for v in a ]

