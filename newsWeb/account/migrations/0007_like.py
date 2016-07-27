# -*- coding: utf-8 -*-
# Generated by Django 1.9.8 on 2016-07-27 19:02
from __future__ import unicode_literals

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('account', '0006_userinfo_user'),
    ]

    operations = [
        migrations.CreateModel(
            name='Like',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('fan', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='fan', to='account.UserInfo')),
                ('star', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, related_name='star', to='account.UserInfo')),
            ],
        ),
    ]
