<template>
  <v-container fluid>
    <v-layout column justify-space-around>
      <h3><img src="../assets/picnic-basket-full-of-raw-vegetables.svg" alt="ingredients"> Ingredients</h3>
      <v-list two-line v-for="(ingrident, id) in $root.ingredients" :key="ingrident.id">
        <ingredient-list-item :value="ingrident"></ingredient-list-item>
      </v-list>
    </v-layout>
  </v-container>
</template>

<script>
import IngredientListItem from '@/components/IngredientListItem'

export default {
  data () {
    return {
    }
  },
  components: {
    IngredientListItem
  }
}
</script>

<style>

</style>
