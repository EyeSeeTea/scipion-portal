# -*- coding: utf-8 -*-
# Generated by Django 1.11 on 2017-07-10 23:09
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('report_protocols', '0002_auto_20170710_2252'),
    ]

    operations = [
        migrations.AddField(
            model_name='ipaddressblacklist',
            name='note',
            field=models.CharField(max_length=128, null=True),
        ),
    ]
