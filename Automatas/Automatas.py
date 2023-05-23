class automata:
    def __init__(self, estados, alfabeto, transiciones, estado_actual, aceptacion):
        self.estados = estados
        self.alfabeto = alfabeto
        self.transiciones = transiciones
        self.estado_actual = estado_actual
        self.aceptacion = aceptacion

    def evaluar(self, entrada):
        for simbolo in entrada:
            if simbolo not in self.alfabeto:
                print('La cadena tiene letras que no estan dentro del alfabeto')
                print('La cadena se rechaza')
                return

            if (self.estado_actual, simbolo) not in self.transiciones:
                print(f'No existe la transicion para el estado {self.estado_actual} y el simbolo {simbolo}')
                return
            
            self.estado_actual = self.transiciones[(self.estado_actual, simbolo)]

        if self.estado_actual in self.aceptacion:
            print('La cadena fue aceptada...')

        else:
            print('La cadena es rechazada')

#Main
if __name__ == '__main__':
    estados = {1, 2, 3, 4, 5, 6}
    alfabeto = {'a', 'b', 'c'}
    aceptacion = {4}
    transiciones ={
        #Transiciones estado 1
        (1, 'a'): 2,
        (1, 'b'): 1,
        (1, 'c'): 6,

        #Transiciones estados 2
        (2, 'a'): 2,
        (2, 'b'): 1,
        (2, 'c'): 3,

        #Transiciones estado 3
        (3, 'a'): 2,
        (3, 'b'): 4,
        (3, 'c'): 5,

        #Transiciones estado 4
        (4, 'a'): 2,
        (4, 'b'): 1,
        (4, 'c'): 6,

        #Transiciones estado 5
        (5, 'a'): 5,
        (5, 'b'): 5,
        (5, 'c'): 5,

        #Transiciones estado 6
        (6, 'a'): 2,
        (6, 'b'): 1,
        (6, 'c'): 5
    }
    
    estado_actual = 1
    a = automata(estados, alfabeto, transiciones, estado_actual, aceptacion)
    entrada = input('Ingrese una cadena a evaluar por favor: ')
    a.evaluar(entrada)



