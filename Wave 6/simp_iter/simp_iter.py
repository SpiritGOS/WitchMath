import sympy


def simp_iter(func, x, y, d=100, eps=0.01):
    n = 0
    vars = sympy.symbols('x y')
    while n < 155 and d > eps:
        x1 = sympy.simplify(func[0]).subs([(vars[0], x), (vars[1], y)]).evalf()
        y1 = sympy.simplify(func[1]).subs([(vars[0], x), (vars[1], y)]).evalf()
        d = (((x - x1)**2 + (y - y1)**2)**(1/2)
             ).subs([(vars[0], x), (vars[1], y)]).evalf()
        print(n, x, y, d)
        x, y = x1, y1
        n += 1


if __name__ == "__main__":
    test = ['(y)**(1/2)', '(4 - x**2)**(1/2)']
    simp_iter(test, 2, 2)
