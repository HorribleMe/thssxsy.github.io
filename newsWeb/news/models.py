from django.db import models
from django.utils import timezone

# Create your models here.
class News(models.Model):
	author = models.ForeignKey('auth.User')
	title = models.CharField(max_length=50)
	content = models.TextField()
	img = models.ImageField(upload_to='images', default='images/default.png')
	time = models.DateTimeField(default=timezone.now)

	def __str__(self):
		return self.title

class Comments(models.Model):
	author = models.ForeignKey('auth.User')
	news = models.ForeignKey('News', related_name='news')
	content = models.TextField()
	time = models.DateTimeField(default=timezone.now)
	support = models.IntegerField(default = 0)
	def __str__(self):
		return self.content
