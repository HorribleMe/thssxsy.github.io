from django.contrib import admin
from .models import News
from .models import Comments
from .models import Save
from .models import Tag

admin.site.register(News)
admin.site.register(Comments)
admin.site.register(Save)
admin.site.register(Tag)
# Register your models here.
