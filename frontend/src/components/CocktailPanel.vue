<template>
    <v-card class="my-4 cocktail">
        <v-card-title primary-title>
          <v-layout column>
              <div class="headline">{{cocktail.name}}</div>
              <div v-for="i in cocktail.items" :key="i.ingredientId">
              {{ingredients[i.ingredientId].name}}
              {{i.ml | toUnit}} cl
              {{ingredients[i.ingredientId].type}}
              </div>
          </v-layout>
        </v-card-title>
        <v-card-actions>
        <v-btn flat @click="">Customize</v-btn>
        <v-spacer></v-spacer>
        <v-btn flat primary @click="order(cocktail)">Order</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
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
  filters: {
    toUnit (txt) {
      return txt / 10
    }
  }
}
</script>

<style scoped>
  .cocktail {

  }
</style>
