# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-28 18:44
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('account', '0007_like'),
    ]

    operations = [
        migrations.AlterField(
            model_name='userinfo',
            name='headPic',
            field=models.ImageField(upload_to='headPic'),
        ),
    ]