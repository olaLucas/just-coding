def busca_binaria(v, key):
    m = (len(v) - 1) // 2
    if m >= 0:  
        if key < v[m]:
            return busca_binaria(v[:m], key)
        elif key > v[m]:
            return busca_binaria(v[m + 1:], key)
        elif key == v[m]:
            return v[m]
    else:
        return None


l = [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ]

print(busca_binaria(l, 9))
