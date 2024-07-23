import tkinter as tk
from tkinter import ttk
import numpy as np

# Functions for joystick controller curves
def f_linear(x, m=1, b=0):
    return m * x + b if x >= 0 else -(m * x + b)

def f_exponential(x, base=np.e, scale=1):
    return scale * (np.power(base, x) - 1) if x >= 0 else -(scale * (np.power(base, -x) - 1))

def f_logarithmic(x, base=np.e, scale=1):
    return scale * (np.log(x + 1) / np.log(base)) if x >= 0 else -(scale * (np.log(-x + 1) / np.log(base)))

def f_s_curve(x, steepness=1, midpoint=0):
    return 1 / (1 + np.exp(-steepness * (x - midpoint))) if x >= 0 else -(1 / (1 + np.exp(steepness * (x + midpoint))))

def f_parabolic(x, a=1, b=0):
    return a * x**2 + b if x >= 0 else -(a * x**2 - b)

def f_cubic(x, a=1, b=0):
    return a * x**3 + b if x >= 0 else -(a * x**3 - b)

def f_quadratic(x, a=1, b=0, c=0):
    return a * x**2 + b * x + c if x >= 0 else -(a * x**2 - b * x + c)

def f_step(x, steps=10, scale=1):
    step_size = 1.0 / steps
    return scale * np.floor(x / step_size) * step_size if x >= 0 else -(scale * np.floor(-x / step_size) * step_size)

def f_dead_zone(x, threshold=0.1, scale=1):
    if abs(x) < threshold:
        return 0
    return scale * x if x >= 0 else -(scale * x)

def f_sensitivity(x, sensitivity=2.0, offset=0):
    return np.power(x, sensitivity) + offset if x >= 0 else -(np.power(-x, sensitivity) - offset)

def f_hybrid(x, split_point=0.5, base=np.e, scale=1):
    return x if x < split_point else scale * (np.power(base, x) - 1) if x >= 0 else -x if x > -split_point else -(scale * (np.power(base, -x) - 1))

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
    "Sensitivity": f_sensitivity,
    "Hybrid": f_hybrid
}

# Function to call the selected curve function and display the result
def calculate():
    func_name = function_var.get()
    func = functions[func_name]
    x_value = float(entry_x.get())
    params = entry_params.get().split(',')
    params = [float(param) for param in params]
    
    try:
        result = func(x_value, *params)
    except TypeError:
        result = "Invalid parameters"
    
    result_label.config(text=f"Result: {result}")

# Create the main window
root = tk.Tk()
root.title("Joystick Controller Curve Calculator")

# Dropdown menu for selecting the function
function_var = tk.StringVar(value="Linear")
function_menu = ttk.Combobox(root, textvariable=function_var, values=list(functions.keys()))
function_menu.grid(row=0, column=1, padx=10, pady=10)

# Entry for x value
tk.Label(root, text="x value:").grid(row=1, column=0, padx=10, pady=10)
entry_x = tk.Entry(root)
entry_x.grid(row=1, column=1, padx=10, pady=10)

# Entry for additional parameters
tk.Label(root, text="Parameters (comma-separated):").grid(row=2, column=0, padx=10, pady=10)
entry_params = tk.Entry(root)
entry_params.grid(row=2, column=1, padx=10, pady=10)

# Button to calculate the result
calculate_button = tk.Button(root, text="Calculate", command=calculate)
calculate_button.grid(row=3, column=1, padx=10, pady=10)

# Label to display the result
result_label = tk.Label(root, text="Result: ")
result_label.grid(row=4, column=1, padx=10, pady=10)

# Run the Tkinter event loop
root.mainloop()

