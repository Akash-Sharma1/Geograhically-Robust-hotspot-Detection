from django.urls import path

from . import views

urlpatterns = [
    path('add/', views.add, name='add'),
    path('', views.show, name='show'),
    path('draw/', views.draw, name='draw'),
]