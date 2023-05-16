import {NgModule} from '@angular/core';
import {BrowserModule} from '@angular/platform-browser';

import {AppRoutingModule} from './app-routing.module';
import {AppComponent} from './app.component';
import {RecipeShowComponent} from './service/recipes/recipe-show/recipe-show.component';
import {IngredientShowComponent} from './service/ingredients/ingredient-show/ingredient-show.component';
import {InstructionShowComponent} from './service/instructions/instruction-show/instruction-show.component';
import {HomeComponent} from './common/home/home.component';
import {HttpClientModule} from "@angular/common/http";

@NgModule({
    declarations: [
        AppComponent,
        RecipeShowComponent,
        IngredientShowComponent,
        InstructionShowComponent,
        HomeComponent
    ],
    imports: [
        BrowserModule,
        AppRoutingModule,
        HttpClientModule,
    ],
    providers: [],
    bootstrap: [AppComponent]
})
export class AppModule {
}
