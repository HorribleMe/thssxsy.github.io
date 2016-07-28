from django.db import models
from django.utils import timezone

# Create your models here.
class Tag(models.Model):
	name = models.CharField(max_length=30, default='None')
	newsNum = models.IntegerField(default=0)

	def __str__(self):
		return self.name

class News(models.Model):
	author = models.ForeignKey('auth.User')
	classify = models.ForeignKey('Tag', related_name='classify')
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

class Save(models.Model):
	user = models.ForeignKey('auth.User')
	news = models.ForeignKey('News', related_name='saveNews')

