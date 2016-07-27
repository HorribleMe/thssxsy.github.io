from django.contrib import admin
from .models import News
from .models import Comments
from .models import Save

admin.site.register(News)
admin.site.register(Comments)
admin.site.register(Save)
# Register your models here.
