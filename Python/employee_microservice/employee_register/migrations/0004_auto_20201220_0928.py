# Generated by Django 3.1.4 on 2020-12-20 09:28

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('employee_register', '0003_auto_20201219_1937'),
    ]

    operations = [
        migrations.AddField(
            model_name='employee',
            name='city',
            field=models.CharField(default='Israel', max_length=20),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='employee',
            name='country',
            field=models.CharField(default='Tel-Aviv', max_length=20),
            preserve_default=False,
        ),
    ]
