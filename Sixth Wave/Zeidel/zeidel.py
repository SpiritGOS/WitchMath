import sympy


def zeidel(func, x, y, d, eps):
    n = 0
    vars = sympy.symbols('x y')
    while ((n < 155) and (d > eps)):
        r = sympy.simplify(func[0]).subs([(vars[0], x), (vars[1], y)]).evalf()
        d = (x-r)**2
        x = r
        r = sympy.simplify(func[1]).subs([(vars[0], x), (vars[1], y)]).evalf()
        d += (y-r)**2
        y = r
        d = d**(1/2)
        n +=1
        print(f'n = {n}, x = {x:.9f}, y = {y:.9f}, d = {d}')


if __name__ == "__main__":
    test = ['(y)**(1/2)', '(4 - x**2)**(1/2)']
    zeidel(test, 2, 2, 100, 0.01)