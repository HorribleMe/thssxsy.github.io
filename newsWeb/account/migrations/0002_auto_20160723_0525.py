# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-22 21:25
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('account', '0001_initial'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='news',
            name='author',
        ),
        migrations.DeleteModel(
            name='News',
        ),
    ]