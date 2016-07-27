from django import forms
from .models import Comments

class CommentsForm(forms.ModelForm):
	class Meta:
		model = Comments
		fields = ('content',)

class SearchForm(forms.Form):
	title = forms.CharField(max_length=50)

class SearchByContent(forms.Form):
	content = forms.CharField(max_length=50)