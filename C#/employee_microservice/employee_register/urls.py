from django.urls import path, include
from . import views

urlpatterns = [
    path('', views.employee_form, name='employee_form'), # for the GET and POST requests for insert operations
    path('<int:id>/', views.employee_form, name='employee_update'),  # for the GET and POST req. for update operation
    path('delete/<int:id>/', views.employee_delete, name='employee_delete'),
    path('convert/<int:id>/', views.convert_currency, name='convert_currency'),
    path('list/', views.employee_list)
]
