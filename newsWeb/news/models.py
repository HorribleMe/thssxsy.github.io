from django.db import models
from django.utils import timezone

# Create your models here.
class News(models.Model):
	author = models.ForeignKey('auth.User')
	title = models.CharField(max_length=50)
	content = models.TextField()
	time = models.DateTimeField(default=timezone.now)

	def __str__(self):
		return self.title

