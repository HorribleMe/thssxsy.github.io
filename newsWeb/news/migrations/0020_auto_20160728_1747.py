# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-28 09:47
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('news', '0019_auto_20160728_1746'),
    ]

    operations = [
        migrations.AlterField(
            model_name='news',
            name='classify',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='classify', to='news.Tag'),
        ),
    ]
