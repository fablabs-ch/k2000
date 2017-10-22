<template>
    <v-card class="my-4 cocktail">
        <v-card-title primary-title :style="{'background': color}">
          <v-layout column>
              <div class="headline">{{cocktail.name}}</div>
              <div v-for="i in cocktail.items" :key="i.ingredientId">
              {{i.ml | toUnit}} cl
              <ingredient-type style="display: inline-block;" :type="ingredients[i.ingredientId].type" :style="{'background-color': ingredients[i.ingredientId].color}"></ingredient-type>
               {{ingredients[i.ingredientId].name}}
              </div>
              <img class="icon" v-if="cocktail.shakeYourBody" src="../assets/shaker.svg" alt="shaker">
          </v-layout>
        </v-card-title>
        <v-card-actions>
        <v-btn flat outline  @click="">Customize</v-btn>
        <v-spacer></v-spacer>
        <v-btn color="primary" @click="order(cocktail)">Order</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
import IngredientType from '@/components/IngredientType'
import ColorMixer from '../../node_modules/colormix/src/index'

export default {
  props: ['cocktail'],
  data () {
    return {
      ingredients: this.$root.ingredients
    }
  },
  methods: {
    order (cocktail) {
      this.$http.post('/api/command/order', cocktail.items).then(response => {
        this.$emit('Order sent to server TODO change me')
      })
    }
  },
  computed: {
    color () {
      // calculate % mix or gradiant based on shake
      const calculation = this.cocktail.items.reduce((list, i) => {
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
  .cocktail {

  }

  .icon {
    width: 40px;
  }
</style>
