from django.db import models

# Create your models here.
class Coordinates(models.Model):
    lat=models.FloatField()
    longt=models.FloatField()
    