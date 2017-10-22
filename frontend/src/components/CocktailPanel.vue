<template>
    <v-card class="my-4 cocktail">
        <v-card-title primary-title :style="{'background': color}">
          <v-layout column>
              <v-layout row class="headline">
                <v-flex>
                  {{cocktail.name}}
                  <img class="icon" v-if="cocktail.shakeYourBody" src="../assets/shaker.svg" alt="shaker">
                </v-flex>
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
                    <v-text-field hide-details v-if="mode !== ORDER" :disabled="ing.disabled" class="qty-edit" type="number" :value="ing.ml | toUnit" @input="setIngQty(ing, $event)"></v-text-field>
                    <span v-if="mode === ORDER" class="qty">{{ing.ml | toUnit}}</span>
                    &nbsp;cl
                    <ingredient-type class="type" style="display: inline-block;" :type="ingredients[ing.ingredientId].type" :style="{'background-color': ingredients[ing.ingredientId].color}"></ingredient-type>
                    <v-flex flex class="i-name">{{ingredients[ing.ingredientId].name}}</v-flex>
                    <v-btn flat icon v-if="mode === CUSTOMIZE && !ing.disabled" @click.native="toggle(ing)"><v-icon>remove_circle_outline</v-icon></v-btn>
                    <v-btn flat icon v-if="mode === CUSTOMIZE && ing.disabled" @click.native="toggle(ing)"><v-icon>add_circle_outline</v-icon></v-btn>
                    <v-btn flat icon v-if="mode === EDIT" @click.native="removeIngredient(ing)"><v-icon>delete</v-icon></v-btn>
                  </v-layout>
                </v-list-tile>
                ADD / custom
              </v-list>
          </v-layout>
        </v-card-title>
        <v-card-actions>
        <v-btn v-if="mode === ORDER" flat outline @click="mode = CUSTOMIZE">Customize</v-btn>
        <v-btn v-if="mode === CUSTOMIZE" flat outline @click="reset">Reset</v-btn>
        <v-btn v-if="mode === EDIT" flat outline  @click="duplicate">Duplicate</v-btn>

        <v-spacer></v-spacer>
        <v-btn v-if="mode !== EDIT" color="primary" @click="order">Order</v-btn>
        <v-btn v-if="mode === EDIT" flat outline  @click="reload">Cancel</v-btn>
        <v-btn v-if="mode === EDIT" color="primary" @click="save">Save</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
import Vue from 'vue'
import IngredientType from '@/components/IngredientType'
import ColorMixer from '../../node_modules/colormix/src/index'

export default {
  props: ['cocktail'],
  data () {
    return {
      ORDER: 'ORDER',
      CUSTOMIZE: 'CUSTOMIZE',
      EDIT: 'EDIT',
      mode: 'ORDER',
      ingredients: this.$root.ingredients
    }
  },
  methods: {
    setTotal (val) {
      this.total = parseInt(val) * 10
    },
    order () {
      const order = Object.assign({}, this.cocktail)
      order.items = this.cocktail.items.map(i => Object.assign({}, i))
      this.$emit('order', order)
    },
    save () {
      console.log('TODO send to server')
      this.mode = this.ORDER
    },
    duplicate () {
      console.log('TODOremove id and save as new?')
      this.mode = this.ORDER
    },
    cancel () {
      console.log('TODO handle cancel of edits reload?')
      this.mode = this.ORDER
    },
    reset () {
      this.cocktail.items.filter(i => !i.custom).forEach(i => {
        i.ml = i.mlOriginal
        i.disabled = false
      })
      this.mode = this.ORDER
    },
    toggle (i) {
      i.disabled = !i.disabled
      // hack to trigger list refresh for now...
      Vue.set(this.cocktail, 'items', this.cocktail.items.slice(0))
    },
    removeIngredient (ing) {
      this.cocktail.items.splice(this.cocktail.items.indexOf(ing), 1)
    }
  },
  computed: {
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
        list.colors.push(new ColorMixer.Color(this.ingredients[i.ingredientId].color))
        list.hexColors.push(this.ingredients[i.ingredientId].color)
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
  }
</style>
