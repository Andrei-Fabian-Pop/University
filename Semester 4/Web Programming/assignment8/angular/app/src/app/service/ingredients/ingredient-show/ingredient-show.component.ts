import {Component, OnInit} from '@angular/core';
import {HttpClient} from "@angular/common/http";
import {Router} from "@angular/router";
import {backendUrl} from "../../../.constants";
import {Observable} from "rxjs";
import {Ingredient} from "../../../models/ingredient";

@Component({
  selector: 'app-ingredient-show',
  templateUrl: './ingredient-show.component.html',
  styleUrls: ['./ingredient-show.component.css']
})
export class IngredientShowComponent implements OnInit {
    protected ingredients: Array<Ingredient> = [];
    protected selectedIngredient: Ingredient | null = null;
    private readonly table_name = "Ingredients";

    protected offset = 0;
    protected limit = 5;

    selectIngredient(ingredient: Ingredient) {
        this.selectedIngredient = ingredient;
    }

    constructor(private http: HttpClient, private router: Router) {
    }

    ngOnInit(): void {
        this.pullIngredients(this.offset, this.limit);
    }

    pullIngredients(offset: number, limit: number): void {
        this.refresh(offset, limit).subscribe(ingredients => this.ingredients = ingredients);
    }

    insertIngredient(name: string): void {
        this.http.post(backendUrl + `add.php`, {
            table_name: this.table_name,
            data: {
                name: name,
            }
        }).subscribe((result) => {
            console.log(result);
        });
    }

    updateIngredient(name: string): void {
        if (name == null) {
            alert("missing name field");
            return;
        }
        this.http.patch(backendUrl + `update.php`, {
            table_name: this.table_name,
            id: this.selectedIngredient?.id,
            data: {
                name: name
            }
        }).subscribe((result) => {
            console.log(result);
            this.pullIngredients(this.offset, this.limit);
        });
    }

    deleteIngredient(): void {
        let id_to_send;
        if (this.selectedIngredient?.id !== undefined) {
            id_to_send = this.selectedIngredient.id;
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
            this.pullIngredients(this.offset, this.limit);
            this.selectedIngredient = null;
        });
    }

    refresh(offset: number, limit: number): Observable<Ingredient[]> {
        return this.http.get<Ingredient[]>(backendUrl + `show.php`, {
            params: {
                table_name: this.table_name,
                offset: offset.toString(),
                limit: limit.toString(),
            }
        });
    }

    nextPage() {
        this.refresh(this.offset + this.limit, this.limit).subscribe(ingredients => {
            if (ingredients.length != 0) {
                this.offset += this.limit;
                this.ingredients = ingredients;
            }
        });
    }

    prevPage() {
        if (this.offset - this.limit >= 0) {
            this.offset -= this.limit;

            this.pullIngredients(this.offset, this.limit);
        }
    }
}
