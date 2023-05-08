from django.shortcuts import render

# Create your views here.
import math

def calculate_bmi(request):
    if request.method == 'POST':
        ft = int(request.POST.get('ft'))
        inches = int(request.POST.get('inches'))
        weight = float(request.POST.get('weight'))
        
        heighttotal = (ft * 12) + inches
        height = (heighttotal * 0.025)**2
        weight = weight * 0.45
        bmi = weight / height
        
        if bmi > 0:
            if bmi <= 18.5:
                category = "underweight"
            elif bmi <= 25:
                category = "normal weight"
            elif bmi <= 30:
                category = "overweight"
            else:
                category = "obese"
        else:
            category = ""
            
        context = {
            'bmi': round(bmi),
            'category': category
        }
        return render(request, 'bmi.html', context)
        
    else:
        return render(request, 'calculate_bmi.html')
