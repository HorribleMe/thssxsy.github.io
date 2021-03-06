# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-27 13:09
from __future__ import unicode_literals

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('news', '0013_comments_commentuserinfo'),
    ]

    operations = [
        migrations.AlterField(
            model_name='comments',
            name='author',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='auth', to=settings.AUTH_USER_MODEL),
        ),
        migrations.AlterField(
            model_name='comments',
            name='commentUserInfo',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='userInfo', to='account.UserInfo'),
        ),
        migrations.AlterField(
            model_name='comments',
            name='news',
            field=models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='news', to='news.News'),
        ),
    ]
