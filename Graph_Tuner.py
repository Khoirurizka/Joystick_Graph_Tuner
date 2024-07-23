import tkinter as tk
from tkinter import ttk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import sympy as sp

import sympy as sp

# Linear Curve with gradient
def f_linear(x, a=1, b=0):
    return a * x + b

# Exponential Curve with base and scale
def f_exponential(x, a=sp.E, b=1):
    return b * (sp.Pow(a, x) - 1)
    '''
    if x >= 0:
        return b * (sp.Pow(a, x) - 1)
    else:
        return -(b * (sp.Pow(a, -x) - 1))
    '''
# Logarithmic Curve with base and scale
def f_logarithmic(x, a=sp.E, b=1):
    return b * (sp.log(x + 1) / sp.log(a))
    '''
    if x >= 0:
        return b * (sp.log(x + 1) / sp.log(a))
    else:
        return -(b * (sp.log(-x + 1) / sp.log(a)))
    '''
# S-Curve (Sigmoid Curve) with steepness and midpoint
def f_s_curve(x, a=1, b=0):
    return 1 / (1 + sp.exp(-a * (x - b)))
    '''
    if x >= 0:
        return 1 / (1 + sp.exp(-a * (x - b)))
    else:
        return -(1 / (1 + sp.exp(a * (x + b))))
    '''
# Parabolic Curve with coefficient and offset
def f_parabolic(x, a=1, b=0):
    return a * x**2 + b
    '''
    if x >= 0:
        return a * x**2 + b
    else:
        return -(a * x**2 - b)
    '''
# Cubic Curve with coefficient and offset
def f_cubic(x, a=1, b=0):
    return a * x**3 + b * x**2

# Quadratic Curve with coefficients
def f_quadratic(x, a=1, b=0):
    return a * x**2 + b * x
    '''
    if x >= 0:
        return a * x**2 + b * x
    else:
        return -(a * x**2 - b * x)
    '''
# Step Curve with number of steps and scale
def f_step(x, a=10, b=1):
    step_size = 1.0 / a
    return b * sp.floor(x / step_size) * step_size
    '''
    if x >= 0:
        return b * sp.floor(x / step_size) * step_size
    else:
        return -(b * sp.floor(-x / step_size) * step_size)
    '''
# Dead Zone Curve with threshold and scale
def f_dead_zone(x, a=0.1, b=1):
    return b * x
'''
    if abs(x) < a:
        return 0
    elif x >= 0:
        return b * x
    else:
        return -(b * x)
'''
# Sensitivity Curve with sensitivity level and offset
def f_sensitivity(x, a=2.0, b=0):
    return sp.Pow(x, a) + b
    '''
    if x >= 0:
        return sp.Pow(x, a) + b
    else:
        return -(sp.Pow(-x, a) - b)
    '''

# Mapping function names to their corresponding implementations
functions = {
    "Linear": f_linear,
    "Exponential": f_exponential,
    "Logarithmic": f_logarithmic,
    "S-Curve": f_s_curve,
    "Parabolic": f_parabolic,
    "Cubic": f_cubic,
    "Quadratic": f_quadratic,
    "Step": f_step,
    "Dead Zone": f_dead_zone,
    "Sensitivity": f_sensitivity
}

class CircularSlider(tk.Canvas):
    def __init__(self, parent, from_, to, command=None, **kwargs):
        super().__init__(parent, **kwargs)
        self.from_ = from_
        self.to = to
        self.command = command
        self.value = (from_ + to) / 2
        
        self.slider_length = 200
        self.knob_radius = 5
        self.knob_color = 'blue'
        
        self.bind("<Button-1>", self.on_click)
        self.bind("<B1-Motion>", self.on_drag)
        self.bind("<Configure>", self.on_resize)
        
        self.draw_slider()

    def draw_slider(self):
        self.delete("all")
        self.create_line(self.knob_radius, self.winfo_height() // 2,
                         self.slider_length - self.knob_radius, self.winfo_height() // 2, fill="gray", width=2)
        self.draw_knob()

    def draw_knob(self):
        x = self.value_to_x(self.value)
        y = self.winfo_height() // 2
        self.create_oval(x - self.knob_radius, y - self.knob_radius,
                         x + self.knob_radius, y + self.knob_radius, fill=self.knob_color, outline="")

    def value_to_x(self, value):
        return (value - self.from_) / (self.to - self.from_) * (self.slider_length - 2 * self.knob_radius) + self.knob_radius

    def x_to_value(self, x):
        return (x - self.knob_radius) / (self.slider_length - 2 * self.knob_radius) * (self.to - self.from_) + self.from_

    def on_click(self, event):
        self.value = self.x_to_value(event.x)
        self.draw_slider()
        if self.command:
            self.command(self.value)

    def on_drag(self, event):
        self.value = self.x_to_value(event.x)
        self.draw_slider()
        if self.command:
            self.command(self.value)

    def on_resize(self, event):
        self.slider_length = event.width
        self.draw_slider()
        
class GraphTuner(tk.Tk):
    def __init__(self):
        super().__init__()

        self.cpp_text = tk.Text(self, height=5, width=50, wrap=tk.WORD)
        self.cpp_text.config(state=tk.DISABLED)
        # Dropdown menu for selecting the function 
        self.function_var = tk.StringVar(value="Linear")

        #Graph
        self.fig = Figure(figsize=(5, 5), dpi=100)
        self.canvas = FigureCanvasTkAgg(self.fig, master=self)
        self.ax = self.fig.add_subplot(111)
        self.a_val = 1
        self.b_val = 0
        self._input = 0
        
        self.title("Joystick Graph Tuner")
        self.geometry("500x1000")

        self._init_plot()
        self.create_widgets()
        

    def create_widgets(self):
        style = ttk.Style()
        style.configure("TScale",
                        sliderlength=50)  # Increase the slider handle siz
    
        # Title Label
        label = tk.Label(self, text="Joystick Graph Tuner", font=("Helvetica", 14))
        label.pack(pady=10)
        # Create a label to display the generated C++ code
        self.cpp_label = tk.Label(self, text="\nGenerated C++ code:")
        self.cpp_label.pack()
        # Create a text widget to display the generated C++ code
        self.cpp_text.pack()
        # Button to calculate the result
        self.calculate_button = tk.Button(self, text="Generate c++", command=self.update_equation)
        self.calculate_button.pack()
        #self.calculate_button.grid(row=1, column=1, padx=10, pady=10)
        # Dropdown menu for selecting the function 
        self.function_menu = ttk.Combobox(self, textvariable=self.function_var, values=list(functions.keys())) 
        self.function_menu.pack()
        self.function_menu.bind("<<ComboboxSelected>>", self.call_update_graph)
        #self.calculate_button.grid(row=0, column=1, padx=10, pady=10)
        
        # Input Val
        input_label = tk.Label(self, text="Input")
        input_label.pack()
        self.var_input_slider = CircularSlider(self, from_=-1, to=1, command=self.update_input_point, bg="white", height=50)
        self.var_input_slider.pack(pady=5, padx=20, fill='x')

        # Param a val
        dead_zone_label = tk.Label(self, text="Param a")
        dead_zone_label.pack()
        self.param_a_slider = CircularSlider(self, from_=-10, to=10, command=self.update_param_a, bg="white", height=50)
        self.param_a_slider.pack(pady=5, padx=20, fill='x')

        # Param b val
        dead_zone_label = tk.Label(self, text="Param b")
        dead_zone_label.pack()
        self.param_b_slider = CircularSlider(self, from_=-10, to=10, command=self.update_param_b, bg="white", height=50)
        self.param_b_slider.pack(pady=5, padx=20, fill='x')
    
    def call_update_graph(self,event):
        self.update_graph()
   
    def convert_equation(self,equation_func,x,a,b):
        x_sym, a_sym, b_sym  = sp.symbols('x a b')
        equation = equation_func(x_sym, a_sym, b)
        equation_subs_lv1 = equation.subs(a_sym, a)
        equation_subs_lv2 = equation_subs_lv1.subs(b_sym, b)
        cpp_code = sp.ccode(equation_subs_lv2)
        return equation, cpp_code  
        
        
    def update_equation(self):
        selected_func = self.func
        equation, cpp_code = self.convert_equation(selected_func,self._input,self.a_val, self.b_val)
        
        #self.symbolic_text.config(state=tk.NORMAL)
        self.cpp_text.config(state=tk.NORMAL)
    
        #self.symbolic_text.delete(1.0, tk.END)
        self.cpp_text.delete(1.0, tk.END)
    
        #self.symbolic_text.insert(tk.END, str(equation))
        self.cpp_text.insert(tk.END, cpp_code)
    
        #self.symbolic_text.config(state=tk.DISABLED)
        self.cpp_text.config(state=tk.DISABLED)
        
    def _init_plot(self):
        self.x = np.arange(-1, 1.001, 0.001) 
        self.update_graph()
        '''
        self.ax.set_xlabel('input')
        self.ax.set_ylabel('')
        self.ax.set_xlim(-1, 1)
        self.ax.set_ylim(-1, 1)
        
        self.ax.axhline(0, color='black',linewidth=0.5)
        self.ax.axvline(0, color='black',linewidth=0.5)
        

        self.canvas .draw()
        self.canvas.get_tk_widget().pack(pady=20)
        '''
    def update_graph(self):
        func_name = self.function_var.get()
        self.func = functions[func_name]
        #self.update_equation()
        '''
        x_value = float(entry_x.get())
        params = entry_params.get().split(',')
        params = [float(param) for param in params]
    
        try:
            result = func(x_value, *params)
        except TypeError:
            result = "Invalid parameters"
        '''
    
        self.ax.cla()
        self.ax.set_xlabel('input')
        self.ax.set_ylabel('')
        self.ax.set_xlim(-1, 1)
        self.ax.set_ylim(-1, 1)
        
        self.ax.axhline(0, color='black',linewidth=0.5)
        self.ax.axvline(0, color='black',linewidth=0.5)

        _percentage = self.func(self._input,self.a_val,self.b_val)
        
        y = [self.func(i,self.a_val,self.b_val) for i in self.x]
        self.ax.plot(self.x, y)

        self.ax.plot(self._input,self.func(self._input, self.a_val,self.b_val), 'ro')

        self.canvas .draw()
        self.canvas.get_tk_widget().pack(pady=20)
        
    def update_input_point(self, value):
        self._input = float(value)
        self.update_graph()
        
    def update_param_a(self, value):
        self.a_val = float(value)
        self.update_graph()

        self.canvas .draw()
        self.canvas.get_tk_widget().pack(pady=20)
    def update_param_b(self, value):
        self.b_val = float(value)
        self.update_graph()

if __name__ == "__main__":
    app = GraphTuner()
    app.mainloop()

