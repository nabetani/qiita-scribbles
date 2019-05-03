def make_tarai():
    cache = {}
    def tarai(x, y, z):
        if x <= y:
            return y
        key = (x, y, z)
        val = cache.get(key)
        if val is not None:
            return val
        val = tarai(
            tarai(x-1, y, z),
            tarai(y-1, z, x),
            tarai(z-1, x, y)
        )
        cache[key] = val
        return val
    return tarai

tarai = make_tarai()
print(tarai(400, 50, 0))