# to change class attribute 

class Person:
    name = "Stranger"
    '''def changeName(self, name):
        self.name = name
        # Person.name = name ( this will change the class attribute )
        # Or
        # self.__class__.name = "Hemant"
    '''
    # Or
    @classmethod
    def changeName(cls,name):
        cls.name = name
        

p1 = Person()
p1.changeName("Hemant")
print(p1.name)
print(Person.name)

# Polymorphism

# when the same operator allow to have different meaning according to the context 

# Dhunder functions

# program to add two complex numbers using dhunder  function

class Complex:
    def __init__(self,real,img):
        self.real = real
        self.img = img

    def ShowNumber(self):
        print(self.real,"i + ",self.img,"j")
    
    def __add__(self,num2):
        newReal = self.real + num2.real
        newImg = self.img + num2.img
        return Complex(newReal, newImg)


num1 = Complex(3,4)
num1.ShowNumber()
num2 = Complex(1,6)
num2.ShowNumber()

num3 = num1 + num2
num3.ShowNumber()

# this is operator overloading and use of polymorphism


