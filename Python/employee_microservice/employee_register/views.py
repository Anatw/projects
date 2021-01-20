import requests
from django.shortcuts import render, redirect
from .forms import EmployeeForm
from .models import Employee

# Create your views here.
def employee_list(request):
    context = {'employee_list': Employee.objects.all()}
    return render(request, "employee_register/employee_list.html", context)

# This function is meant to deal with GET and POST (insert/ edit) operations of employees from/to the database
def employee_form(request, id=0):
    if request.method == "GET":
        if id == 0: # This is an insert operation
            form = EmployeeForm()
        else: # This is an edit operation
            employee = Employee.objects.get(pk=id)
            form = EmployeeForm(instance=employee)
        return render(request, "employee_register/employee_form.html", {'form': form})
    else: # This ia POST request - save the data
        if id == 0: # This is an insert operation
            form = EmployeeForm(request.POST)
        else: # This is an update operation
            employee = Employee.objects.get(pk=id)
            form = EmployeeForm(request.POST, instance=employee)
        if form.is_valid():
            form.save()
        return redirect('/employee/list')

# Function to delete an employee record from the database
def employee_delete(request, id):
    employee = Employee.objects.get(pk=id)
    employee.delete()
    return redirect('/employee/list')


def convert_currency(request, id):
    employee = Employee.objects.get(pk=id)
    salary = employee.salary

    url = 'https://free.currconv.com/api/v7/convert?q={}&compact=ultra&apiKey=####'
    currency = 'USD_ILS,ILS_USD'

    res = requests.get(url.format(currency))

    current_currency = float(res.json()['USD_ILS']) * salary
    context = {'current_currency': current_currency}
    return render(request, 'employee_register/convert_currency.html', context)
