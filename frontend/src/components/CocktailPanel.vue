<template>
    <v-card class="my-4 cocktail">
        <v-card-title primary-title :style="{'background': color}">
          <v-layout column>
              <v-layout row class="headline">
                <v-flex flex>
                  <v-text-field v-if="mode === EDIT" hide-details v-model="cocktail.name"></v-text-field>
                  <span v-else>{{cocktail.name}}</span>
                </v-flex>
                <div>
                  <v-layout row>
                    <img class="icon" v-if="cocktail.shakeYourBody" src="../assets/shaker.svg" alt="shaker">
                    <v-checkbox hide-details v-if="mode === EDIT" v-model="cocktail.shakeYourBody"></v-checkbox>
                  </v-layout>
                </div>
                <v-btn flat icon v-if="mode === ORDER" @click.native="mode = EDIT"><v-icon>mode_edit</v-icon></v-btn>
              </v-layout>
              <v-list class="ingredients">
                <v-list-tile v-if="mode === CUSTOMIZE">
                 <v-text-field hide-details class="total" type="number" :value="total | toUnit" @input="setTotal"></v-text-field>
                 <span>cl</span>
                 <span class="type"></span>
                 <v-flex class="i-name">Total</v-flex>
                </v-list-tile>
                <v-list-tile v-for="ing in cocktail.items" :key="ing.ingredientId" :class="{disabled: ing.disabled}">
                  <v-layout row  class="ingredient">
                    <v-text-field hide-details v-if="mode !== ORDER" :disabled="ing.disabled" class="qty-edit" type="number" min="0" :value="ing.ml | toUnit" @input="setIngQty(ing, $event)"></v-text-field>
                    <span v-if="mode === ORDER" class="qty">{{ing.ml | toUnit}}</span>
                    &nbsp;cl
                    <ingredient-type class="type" style="display: inline-block;" :type="ingredientsLookup[ing.ingredientId].type" :style="{'background-color': ingredientsLookup[ing.ingredientId].color}"></ingredient-type>
                    <v-flex flex class="i-name">{{ingredientsLookup[ing.ingredientId].name}}</v-flex>
                    <v-btn flat icon v-if="mode === CUSTOMIZE && !ing.disabled" @click.native="toggle(ing)"><v-icon>remove_circle_outline</v-icon></v-btn>
                    <v-btn flat icon v-if="mode === CUSTOMIZE && ing.disabled" @click.native="toggle(ing)"><v-icon>add_circle_outline</v-icon></v-btn>
                    <v-btn flat icon v-if="mode === EDIT" @click.native="removeIngredient(ing)"><v-icon>delete</v-icon></v-btn>
                  </v-layout>
                </v-list-tile>
                <v-list-tile v-if="mode === CUSTOMIZE || mode === EDIT">
                  <v-layout row  class="ingredient">
                    <v-text-field hide-details class="qty-edit" type="number" min="0" :value="newIngredient.ml | toUnit" @input="setIngQty(newIngredient, $event)"></v-text-field>
                    &nbsp;cl
                    <ingredient-type v-if="newIngredient && newIngredient.ingredientId" class="type" style="display: inline-block;" :type="ingredientsLookup[newIngredient.ingredientId].type" :style="{'background-color': ingredientsLookup[newIngredient.ingredientId].color}"></ingredient-type>
                    <v-flex flex class="i-name">
                              <v-select
              :items="ingredients"
              v-model="newIngredient.ingredientId"
              item-value="id"
              item-text="name"
              label="Ingredient"
              autocomplete
              single-line
              bottom
              required
            ></v-select>
                    </v-flex>
                    <v-btn flat icon @click.native="addIngredient"><v-icon>add</v-icon></v-btn>
                  </v-layout>
                </v-list-tile>
              </v-list>
          </v-layout>
        </v-card-title>
        <v-card-actions>
        <v-btn v-if="mode === ORDER" flat outline @click="mode = CUSTOMIZE">Customize</v-btn>
        <v-btn v-if="mode === CUSTOMIZE" flat outline @click="reset">Reset</v-btn>
        <v-btn v-if="mode === EDIT" flat outline  @click="duplicate">Duplicate</v-btn>
        <v-btn v-if="mode === EDIT" flat color="error" outline  @click="deleteItem">Delete</v-btn>

        <v-spacer></v-spacer>
        <v-btn v-if="mode !== EDIT" color="primary" @click="order">Order</v-btn>
        <v-btn v-if="mode === EDIT" flat outline  @click="cancel">Cancel</v-btn>
        <v-btn v-if="mode === EDIT" color="primary" @click="save">Save</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
import Vue from 'vue'
import IngredientType from '@/components/IngredientType'
import ColorMixer from '@/vendors/colormix'

export default {
  props: ['cocktail'],
  data () {
    return {
      ORDER: 'ORDER',
      CUSTOMIZE: 'CUSTOMIZE',
      EDIT: 'EDIT',
      mode: 'ORDER',
      ingredientsLookup: this.$root.ingredients,
      newIngredient: this.createNewIngrident()
    }
  },
  methods: {
    createNewIngrident () {
      return {
        ingredientId: null,
        ml: 0,
        mlOriginal: 0,
        disabled: false,
        custom: true
      }
    },
    setTotal (val) {
      this.total = parseInt(val) * 10
    },
    order () {
      const order = Object.assign({}, this.cocktail)
      order.items = this.cocktail.items.map(i => Object.assign({}, i))
      this.$emit('order', order)
    },
    deleteItem () {
      this.$http.delete(`recipies/${this.cocktail.id}`).then(response => {
        this.$root.cocktails.splice(this.$root.cocktails.indexOf(this.cocktail), 1)
      }, response => {

      })
    },
    save () {
      this.$http.put(`recipies/${this.cocktail.id}`, this.cocktail).then(response => {
        // TODO update reset params from response.data
        this.$root.notify('saved')
      }, response => {

      })
      this.mode = this.ORDER
    },
    duplicate () {
      const duplicate = Object.assign({}, this.cocktail)
      duplicate.name += ' (copy)'
      delete duplicate.id
      this.$http.post(`recipies`, duplicate).then(response => {
        // TODO update reset params
        this.$root.cocktails.splice(this.$root.cocktails.indexOf(this.cocktail) + 1, 0, response.data)
      }, response => {

      })
      this.mode = this.ORDER
    },
    cancel () {
      this.$http.get(`recipies/${this.cocktail.id}`).then(response => {
        // TODO update reset params
        Object.assign(this.cocktail, response.data)
      }, response => {

      })
      this.mode = this.ORDER
    },
    reset () {
      this.cocktail.items = this.cocktail.itemsOriginal.map(i => {
        i.ml = i.mlOriginal
        i.disabled = false
        i.custom = false
        return i
      })
      this.newIngredient = this.createNewIngrident()
      this.mode = this.ORDER
    },
    toggle (i) {
      i.disabled = !i.disabled
      // hack to trigger list refresh for now...
      Vue.set(this.cocktail, 'items', this.cocktail.items.slice(0))
    },
    addIngredient () {
      this.cocktail.items.push(this.newIngredient)
      this.newIngredient = this.createNewIngrident()
    },
    removeIngredient (ing) {
      this.cocktail.items.splice(this.cocktail.items.indexOf(ing), 1)
    },
    setIngQty (ing, e) {
      ing.ml = parseFloat(e) * 10
      ing.custom = ing.disabled || ing.ml !== ing.mlOriginal
    }
  },
  computed: {
    ingredients () {
      return Object.values(this.$root.ingredients)
    },
    total: {
      get () {
        return this.cocktail.items.filter(i => !i.disabled).reduce((t, i) => {
          return t + i.ml
        }, 0)
      },
      set (target) {
        const ratio = target / this.total
        this.cocktail.items.filter(i => !i.disabled).forEach((i) => {
          i.ml = Math.round(i.ml * ratio)
        })
      }
    },
    color () {
      // calculate % mix or gradiant based on shake
      const calculation = this.cocktail.items.filter(i => !i.disabled).reduce((list, i) => {
        list.colors.push(new ColorMixer.Color(this.ingredientsLookup[i.ingredientId].color))
        list.hexColors.push(this.ingredientsLookup[i.ingredientId].color)
        list.mls.push(i.ml)
        list.total += i.ml
        return list
      }, {
        colors: [],
        hexColors: [],
        mls: [],
        total: 0
      })
      calculation.percentages = calculation.mls.map((ml) => {
        return Math.round(ml / calculation.total * 100)
      })
      const delta = calculation.percentages.reduce((t, x) => t + x, 0) - 100
      if (delta !== 0) {
        calculation.percentages[0] -= delta
      }
      if (this.cocktail.shakeYourBody) {
        return ColorMixer.mix(calculation.colors, calculation.percentages).toString('hex')
      } else {
        let p = 0
        const gradients = calculation.hexColors.map((color, i) => {
          const step = `${color} ${p}%`
          p += calculation.percentages[i]
          return step
        }).join(',')
        return `linear-gradient(to top, ${gradients})`
      }
    }
  },
  filters: {
    toUnit (txt) {
      return txt / 10
    }
  },
  components: {
    IngredientType
  }
}
</script>

<style scoped>
  .headline {
    font-weight: bold;
    font-size: 18pt;
    margin-bottom: 12pt;
  }

  .disabled .qty,
  .disabled .i-name {
    text-decoration: line-through;
  }
  .disabled .type {
    opacity: 0.3;
  }

  .ingredients {
    background-color: rgba(255, 255, 255, 0.3)
  }

  .ingredient {
    font-size: 16pt;
  }

  .total {
    max-width: 42px;
    text-align: right;
  }

  .type {
    margin: 0 20px;
    width: 40px;
  }

  .qty {
    text-align: right;
    width: 60px;
  }

  .qty-edit {
    max-width: 42px;
  }

  .icon {
    width: 40px;
    height: 40px;
  }
</style>
