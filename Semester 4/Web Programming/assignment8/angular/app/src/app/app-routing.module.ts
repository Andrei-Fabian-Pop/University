import {NgModule} from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {HomeComponent} from "./common/home/home.component";
import {RecipeShowComponent} from "./service/recipes/recipe-show/recipe-show.component";
import {IngredientShowComponent} from "./service/ingredients/ingredient-show/ingredient-show.component";
import {InstructionShowComponent} from "./service/instructions/instruction-show/instruction-show.component";

const routes: Routes = [
    {
        path: '',
        component: HomeComponent
    },
    {
        path: 'recipes',
        component: RecipeShowComponent
    },
    {
        path: 'ingredients',
        component: IngredientShowComponent
    },
    {
        path: 'instructions',
        component: InstructionShowComponent
    }
];

@NgModule({
    imports: [RouterModule.forRoot(routes)],
    exports: [RouterModule]
})
export class AppRoutingModule {
}
