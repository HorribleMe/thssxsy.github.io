# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-27 09:07
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('news', '0010_auto_20160727_1701'),
    ]

    operations = [
        migrations.RenameField(
            model_name='comments',
            old_name='userInfo',
            new_name='info',
        ),
    ]
