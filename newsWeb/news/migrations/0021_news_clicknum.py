# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-28 20:35
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('news', '0020_auto_20160728_1747'),
    ]

    operations = [
        migrations.AddField(
            model_name='news',
            name='clickNum',
            field=models.IntegerField(default=0),
        ),
    ]