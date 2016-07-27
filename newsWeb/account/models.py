from django.db import models

# Create your models here.
class UserInfo(models.Model):
	user = models.OneToOneField('auth.User', default=None)
	nickname = models.CharField(max_length = 20, default = 'None')
	email = models.EmailField(default = 'None')
	follow = models.IntegerField(default = 0)
	fans = models.IntegerField(default = 0)
	headPic = models.ImageField(upload_to='headPic', default='headPic/default.jpg')

	def __str__(self):
		return self.nickname

class Like(models.Model):
	star = models.ForeignKey('UserInfo', related_name='star')
	fan = models.ForeignKey('UserInfo', related_name='fan')
