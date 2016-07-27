# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-27 08:49
from __future__ import unicode_literals

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
        ('account', '0002_auto_20160723_0525'),
    ]

    operations = [
        migrations.CreateModel(
            name='AccountInfo',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('nickname', models.CharField(default='None', max_length=20)),
                ('email', models.EmailField(default='None', max_length=254)),
                ('follow', models.IntegerField(default=0)),
                ('fans', models.IntegerField(default=0)),
                ('headPic', models.ImageField(default='headPic/default.jpg', upload_to='headPic')),
                ('account', models.OneToOneField(on_delete=django.db.models.deletion.CASCADE, to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]
