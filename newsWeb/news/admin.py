from django.contrib import admin
from .models import News
from .models import Comments

admin.site.register(News)
admin.site.register(Comments)

# Register your models here.
