// Copyright by Aura

#include "UI/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UAuraWidgetDataController* Controller) {
	if (Controller) {
		WidgetController = Controller;
		OnWidgetControllerSet();
	}
}
