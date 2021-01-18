from django.db import models

class Employee(models.Model):
    fullname = models.CharField(max_length=35)
    country = models.CharField(max_length=20)
    city = models.CharField(max_length=20)
    salary = models.IntegerField()
