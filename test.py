import sympy as sp
import tkinter as tk
from tkinter import ttk

# Define equations as functions
def equation1(t, input_):
    return sp.exp(-t / 10) + sp.exp((sp.Abs(input_) - 100) / 10) * (1 - sp.exp(-t / 10))

def equation2(t, input_):
    return sp.sin(t) + sp.cos(input_)

def equation3(t, input_):
    return sp.sqrt(t**2 + input_**2)

equations = {
    "Exponential Equation": equation1,
    "Sine and Cosine Equation": equation2,
    "Square Root Equation": equation3
}

def convert_equation(equation_func, t_value, input_value):
    t_sym, input_sym = sp.symbols('t input_')
    equation = equation_func(t_sym, input_sym)
    equation_subs = equation.subs(t_sym, t_value)
    cpp_code = sp.ccode(equation_subs)
    return equation_subs, cpp_code

def on_select(event=None):
    try:
        t_value = float(t_entry.get())
        selected_func = equations[combo.get()]
        equation, cpp_code = convert_equation(selected_func, t_value, input_)
        
        symbolic_text.config(state=tk.NORMAL)
        cpp_text.config(state=tk.NORMAL)
        
        symbolic_text.delete(1.0, tk.END)
        cpp_text.delete(1.0, tk.END)
        
        symbolic_text.insert(tk.END, str(equation))
        cpp_text.insert(tk.END, cpp_code)
        
        symbolic_text.config(state=tk.DISABLED)
        cpp_text.config(state=tk.DISABLED)
    except ValueError:
        pass

# Create the tkinter window
root = tk.Tk()
root.title("Equation to C++ Code Converter")

# Define the parameters for the equation
input_ = 150.0  # Example value for input

# Create a label for the dropdown menu
combo_label = tk.Label(root, text="Select an equation:")
combo_label.pack()

# Create a dropdown menu
combo = ttk.Combobox(root, values=list(equations.keys()))
combo.pack()
combo.bind("<<ComboboxSelected>>", on_select)

# Create a label for the 't' input
t_label = tk.Label(root, text="Enter value for t:")
t_label.pack()

# Create an entry widget for the 't' input
t_entry = tk.Entry(root)
t_entry.pack()
t_entry.bind("<Return>", on_select)  # Update on pressing Enter

# Create a label to display the symbolic equation
symbolic_label = tk.Label(root, text="Equation in symbolic form:")
symbolic_label.pack()

# Create a text widget to display the symbolic equation
symbolic_text = tk.Text(root, height=5, width=50, wrap=tk.WORD)
symbolic_text.config(state=tk.DISABLED)
symbolic_text.pack()

# Create a label to display the generated C++ code
cpp_label = tk.Label(root, text="\nGenerated C++ code:")
cpp_label.pack()

# Create a text widget to display the generated C++ code
cpp_text = tk.Text(root, height=5, width=50, wrap=tk.WORD)
cpp_text.config(state=tk.DISABLED)
cpp_text.pack()

# Run the tkinter main loop
root.mainloop()

