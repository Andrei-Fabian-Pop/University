import {Component, OnInit} from '@angular/core';
import {Recipe} from "../../../models/recipe";
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";
import {Observable} from "rxjs";
import {backendUrl} from "../../../\.constants"

@Component({
    selector: 'app-recipe-show',
    templateUrl: './recipe-show.component.html',
    styleUrls: ['./recipe-show.component.css']
})

export class RecipeShowComponent implements OnInit {
    protected recipes: Array<Recipe> = [];
    protected selectedRecipe: Recipe | null = null;
    private readonly table_name = "Recipes";

    protected offset = 0;
    protected limit = 5;

    protected filter: string = "";
    protected filter_key: string = "name";

    selectRecipe(recipe: Recipe) {
        this.selectedRecipe = recipe;
    }

    constructor(private http: HttpClient, private router: Router) {
    }

    ngOnInit(): void {
        this.pullRecipes(this.offset, this.limit);
    }

    pullRecipes(offset: number, limit: number): void {
        this.refresh(offset, limit).subscribe(recipes => this.recipes = recipes);
    }

    insertRecipe(name: string, description: string, author: string): void {
        this.http.post(backendUrl + `add.php`, {
            table_name: this.table_name,
            data: {
                name: name,
                description: description,
                author: author
            }
        }).subscribe((result) => {
            console.log(result);
        });
    }

    updateRecipe(name: string, description: string, author: string): void {
        if (name == null) {
            alert("missing name field");
            return;
        }
        if (author == null) {
            alert("missing author field");
            return;
        }
        if (description == null) {
            alert("missing description field");
            return;
        }
        this.http.patch(backendUrl + `update.php`, {
            table_name: this.table_name,
            id: this.selectedRecipe?.id,
            data: {
                name: name,
                description: description,
                author: author
            }
        }).subscribe((result) => {
            console.log(result);
            this.pullRecipes(this.offset, this.limit);
        });
    }

    deleteRecipe(): void {
        let id_to_send;
        if (this.selectedRecipe?.id !== undefined) {
            id_to_send = this.selectedRecipe.id;
        } else {
            alert("no id selected");
            return;
        }

        this.http.delete(backendUrl + `delete.php`, {
            params: {
                table_name: this.table_name,
                id: id_to_send,
            },
        }).subscribe((result) => {
            console.log(result);
            this.pullRecipes(this.offset, this.limit);
            this.selectedRecipe = null;
        });
    }

    refresh(offset: number, limit: number, filter: string = "", key: string = ""): Observable<Recipe[]> {
        return this.http.get<Recipe[]>(backendUrl + `show.php`, {
            params: {
                table_name: this.table_name,
                offset: offset.toString(),
                limit: limit.toString(),
                filter: filter,
                key: key,
            }
        });
    }

    nextPage(): void {
        this.refresh(this.offset + this.limit, this.limit).subscribe(recipes => {
            if (recipes.length != 0) {
                this.offset += this.limit;
                this.recipes = recipes;
            }
        });
    }

    prevPage(): void {
        if (this.offset - this.limit >= 0) {
            this.offset -= this.limit;

            this.pullRecipes(this.offset, this.limit);
        }
    }

    filterRecipes(offset: number, limit: number, filterValue: string): void {
        offset = 0;
        this.refresh(offset, limit, filterValue, this.filter_key).subscribe(response => this.recipes = response);
    }
}
