// Copyright by Aura

#include "UI/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetDataController(UAuraWidgetDataController* Controller) {
	if (Controller) {
		WidgetDataController = Controller;
		OnWidgetDataControllerSet();
	}
}
