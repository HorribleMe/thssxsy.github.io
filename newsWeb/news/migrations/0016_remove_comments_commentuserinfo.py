# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-27 13:28
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('news', '0015_comments_commentuserinfo'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='comments',
            name='commentUserInfo',
        ),
    ]
